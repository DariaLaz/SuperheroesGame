#include "System.h"
#include "Admin.h"
const User* System::userWith(const String& username) const {
	return users[users.find(username)];
}
System* System::system = nullptr;
System& System::getInstance() {
	if (system == nullptr)
	{
		system = new System();
	}
	return *system;
}


const User* System::currentPlayer() const {
	return current;
};

void System::giveMoney() {
	for (size_t i = 0; i < users.size(); i++)
	{
		if (!users[i]->isAdmin())
		{
			Player* current = ((Player*)(users[i]));
			size_t gain = GameConstants::MONEY_GAIN * current->money();
			current->winMoney((gain > GameConstants::START_MONEY) ? gain : GameConstants::START_MONEY);
		}
	}
}


System::System() {
	std::ifstream ifs(FileConstants::SYS_FILE_NAME, std::ios::in | std::ios::binary);
	if (!ifs.is_open())
		throw std::logic_error("Can not open the file!");

	readFromBinary(ifs);
	ifs.close();
	if (users.size() == 0)
	{
		User* user = new Admin("Admin", "Admin", "admin", "Pass1");
		users.add(user);
	}
}

//ADMIN FUNCTIONS
//����� ������������� ������ �� ���� �� ������ ���� �������������� � ������ � ���������.
void System::addUser(const User& user) {
	adminCheck();
	users.add(&user);
}

void System::addUser(const char* firstName,
	const char* lastName,
	const char* username,
	const char* password,
	bool isAdmin) {
	adminCheck();
	User* user = nullptr;
	if (isAdmin)
	{
		user = new Admin(firstName, lastName, username, password);
	}
	else
	{
		user = new Player(firstName, lastName, username, password);
	}
	users.add(user);
}
void System::addUser(const String& firstName,
	const String& lastName,
	const String& username,
	const String& password,
	bool isAdmin) {
	adminCheck();
	User* user = nullptr;
	if (isAdmin)
	{
		user = new Admin(firstName, lastName, username, password);
	}
	else
	{
		user = new Player(firstName, lastName, password, username);
	}
	users.add(user);
}

//����� ������������� ������ �� ���� �� ������� ������� �� ������.
void System::deletePlayer(const String& nickname) {
	adminCheck();

	int idx = users.find(nickname);
	if (idx < 0 || users[idx]->isAdmin())
	{
		throw std::out_of_range("Invalid nickname!");
	}
	Player* current = static_cast<Player*>(users[idx]);
	size_t count = current->superheroesCount();
	for (size_t i = 0; i < count; i++)
	{
		current->changeMode(current->getHeroAt(i), Mode::notBought);
	}
	deleteUserAt(idx);
}

//����� ������������� ������ �� ��� ����� �� ����� ������ ������������ �� ����� ���������� � ������� 
//�������(��� ����������������, ���� ������������� ���� �� ����� ���� ������� � ������ �� ���� �������������) .
void System::printInfo(const String& nickname) const {
	adminCheck();

	int idx = users.find(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");

	}
	users[idx]->print(isAdmin());
}

//����� ������������� ������ �� ���� �� ������ ���� ���������� ��� ��������. � ������, �� �� �������� ���� ������� ����������, ��������������� ��� � ��������� �� ������ �� ������ ���� 3 ����������. ��������������� ������ �� ���� �� ����� ������ ����������, ����� �� ���� ��������� � �� ���� �� ������ ���� �� ��� �� ��������, ��� �� ����� �� ������ ���.
void System::addSuperhero(const Superhero& superhero) {
	adminCheck();

	market.push_back(superhero);
}
void System::addSuperhero(Superhero&& superhero) {
	adminCheck();

	market.push_back(std::move(superhero));
}
void System::addSuperhero(const String& firstName,
	const String& lastName,
	const String& nickname,
	const Power& power,
	size_t strenght,
	double price,
	Mode mode) {
	adminCheck();
	Superhero hero(firstName, lastName, nickname, power, strenght, price, mode);
	market.push_back(std::move(hero));
}
void System::resurrect(const String& nickname) {
	adminCheck();

	int idx = findSuperhero(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	if (market[idx].mode() != Mode::dead)
	{
		throw std::logic_error("This superhero already exists!");
	}
	market[idx].setMode(Mode::notBought);
}


//PLAYER FUNCTIONS
//����� ����� ������ �� ���� �� ������� ������� ��.
void System::deleteMe() {
	userCheck();
	if (current->isAdmin() && users.adminsCount() == 1)
	{
		throw std::logic_error("You are the only admin and cannot be deleted!");
	}
	deleteUserAt(users.find(current->username()));
	current = nullptr;
}
/*����� ����� ������ �� ���� �� ����� ������ �� ������ ������, � ����� �� �������� ���� ������� ������������� �����,
		� ����� ���� ���������� � ����� ���������� ����(��� ������� ����).*/
void System::printUsers() const {
	userCheck();
	for (size_t i = 0; i < users.size(); i++)
	{
		if (!users[i]->isAdmin() || current->isAdmin())
		{
			users[i]->print(current->isAdmin());
		}
	}
} 

//����� ����� ������ �� ���� �� ����� ���������� ���������
void System::results() {
	vector<Player*> players = this->players();
	size_t size = players.size();
	for (size_t i = 0; i < size; i++)
	{
		size_t maxIndex = i;
		for (size_t j = i; j < size; j++)
		{
			if (players[maxIndex]->money() < players[j]->money())
			{
				maxIndex = j;
			}
		}
		if (maxIndex != i)
		{
			swap(players[i], players[maxIndex]);
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		players[i]->print(isAdmin());
	}
}
//��������������� ������ �� ���� �� ����� ������ ����������, ����� �� ���� ��������� � �� ���� �� ������ ���� �� ��� �� ��������, 
//��� �� ����� �� ������ ���.
//����� ����� ������ �� ���� �� ����� ������ �� ���������� (����� � ��� �� ������ ������) � ��� ������� �� ������ ����� ����������. 
//���� ������������ ����������� ������ �� ������� �� ������. �� � ��������� ��������� �� ���� � ��� ����������, 
//����� ���� ����������� �� ���� ����� ���� � ���� ��������� ����� �������� ������.
void System::printMarket() const {
	userCheck();

	for (size_t i = 0; i < market.size(); i++)
	{
		if (market[i].mode() == Mode::notBought || (current->isAdmin() && market[i].mode() == Mode::dead))
		{
			market[i].print(current->isAdmin());
		}
	}
}
//����� ����� ������ �� ���� �� ������� ��������� �� ������� �� �� ��������� � ���������� � ���������.
void System::changeMode(const String& nickname, const Mode& mode) {
	playerCheck();
	((Player*)current)->changeMode(nickname, mode);
}
void System::changeMode(const char* nickname, const Mode& mode) {
	playerCheck();
	((Player*)current)->changeMode(nickname, mode);
}
void System::buy(const String& nickname) {
	buy(nickname.c_str());
}
void System::buy(const char* nickname) {
	playerCheck();
	int idx = findSuperhero(nickname);
	if (idx < 0 || market[idx].mode() != Mode::notBought)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	((Player*)current)->addSuperhero(&market[idx]);
}
//����� ����� ������ �� ���� �� ������� ������ �� ���� ���������� �� ����� ����������.
int System::attack(const String& nickname, const String& userNickname, const String& heroNickname) {
	playerCheck();
	Player& attacker = *((Player*)current);
	Player* defender = nullptr;
	
	vector<Player*> players = this->players();

	if (userNickname == "")
	{
		int superheroIdx = findSuperhero(heroNickname);
		if (superheroIdx == -1)
			throw std::out_of_range("Invalid nickname!");

		if (market[superheroIdx].mode() == Mode::notBought || market[superheroIdx].mode() == Mode::dead)
			throw std::logic_error("Invalid nickname!");

		defender = getSuperheroOwner(superheroIdx, players);

		if (!defender || defender == &attacker)
			throw std::logic_error("Invalid nickname!");
	}
	else
	{
		int idx = users.find(userNickname);
		if (idx < 0 || users[idx]->isAdmin())
		{
			throw std::out_of_range("Invalid username!");
		}
		defender = static_cast<Player*>(users[idx]);
	}

	Superhero& attackHero = *attacker.getHeroAt(attacker.findHero(nickname));

	if (attackHero.mode() != Mode::attack)
	{
		throw std::invalid_argument("Your hero should be in attack mode");
	}

	if (defender->superheroesCount() == 0)
	{
		//��� ����� ������� ���� �����, ����� ���� ������� ����������, �� ������ �� ���������� ����� ��������� � ���� �� ����������� �����, ����� � ���� ��������� ���������� 
		defender->loseMoney(attackHero.strenght());
		//���������� ����� ������ � �� ���� ����
		size_t win = rand() % (2 * attackHero.strenght());
		attacker.winMoney(win);

		return win;
	}
	Superhero* defendHero = nullptr;
	if (heroNickname == "")
	{
		defendHero = defender->getHeroAt(rand() % defender->superheroesCount());
	}
	else
	{
		defendHero = defender->getHeroAt(defender->findHero(heroNickname));
	}
	
	size_t attackerPoints = attackHero.strenght();
	size_t defenderPoints = defendHero->strenght();
	//��� ���������� ����� � � ��������� ��� ����, �� ������� �� ���������� �� � ���� ����� ����� �������
	//� ������, �� ���������� ����� � � ����������� ��� ����, �� ������ ������� �� ������������� ���������� �� ��������
	int cmp = comparePower(attackHero.power(), defendHero->power());
	if (cmp < 0)
	{
		defenderPoints *= 2;
	}
	else if (cmp > 0)
	{
		attackerPoints *= 2;
	}

	//���������� ���������� ������ ���� ���������� �� ���������� �� ��������� � ����� �����
	if (defenderPoints == attackerPoints)
	{
		//���������� ����� �� ������� � �� ���� ����, �� ��������� ���� ���� k.

		size_t lose = rand() % attackHero.strenght();
		attacker.loseMoney(lose);
		return lose * (-1);
	}
	else if (defenderPoints < attackerPoints) {
		//����������� ����� ���� ���� � ������ ��������� �� ������ �� ������������, ����� �� ������������, � ���������� ����� ������ ���� ����� �� ������ �������.
		size_t diff = attackerPoints - defenderPoints;
		attacker.winMoney(diff);
		if (defendHero->mode() == Mode::attack)
		{
			defender->loseMoney(diff);
		}
		defendHero->setMode(Mode::dead);
		defender->removeSuperhero(defendHero);
		return diff;
	}
	else if (defenderPoints > attackerPoints)
	{
		//����������� ������ ���� z, � ���������� ���� ���� �� �������� 2 ���� ��������� �� ������ �� ������������, ����� �� ������������
		size_t diff = attackerPoints - defenderPoints;
		defender->winMoney(rand() % (2 * diff));
		attacker.loseMoney(2 * diff);
		attackHero.setMode(Mode::dead);
		attacker.removeSuperhero(&attackHero);
		return diff * (-2);
	}
}
Player* System::getSuperheroOwner(size_t superheroIdx, vector<Player*>& players) const {

	for (size_t i = 0; i < players.size(); i++)
	{
		size_t currSize = players[i]->superheroesCount();
		for (size_t j = 0; j < currSize; j++)
		{
			if (players[i]->getHeroAt(j) == &market[superheroIdx])
			{
				return players[i];
			}
		}
	}

	return nullptr;
}
void System::login(const String& username, const String& password) {
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->username() == username && users[i]->isPass(password))
		{
			current = users[i];
			return;
		}
	}
	throw std::logic_error("Invalid username or password");
}

void System::logout() {
	current = nullptr;
}
bool System::isLogged() const {
	return current != nullptr;
}
bool System::isAdmin() const {
	return current && current->isAdmin();
}

void System::deleteUserAt(size_t idx) {
	
	users.removeAt(idx);
}
int System::findSuperhero(const String& nickname) const {
	for (size_t i = 0; i < market.size(); i++)
	{
		if (market[i].nickname() == nickname)
		{
			return i;
		}
	}
	return -1;
}
int System::findSuperhero(const char* nickname) const {
	for (size_t i = 0; i < market.size(); i++)
	{
		if (strcmp(market[i].nickname().c_str(), nickname) == 0)
		{
			return i;
		}
	}
	return -1;
}



void System::userCheck() const {
	if (!current)
	{
		throw std::logic_error("There is no logged in user!");
	}
}
void System::adminCheck() const {
	if (!isAdmin())
	{
		throw std::logic_error("Not an admin!");
	}
}
void System::playerCheck() const {
	if (!current || isAdmin())
	{
		throw std::logic_error("Not a player!");
	}
}

int comparePower(const Power& pow1, const Power& pow2) {
	if ((pow1 == Power::fire && pow2 == Power::earth)
		|| (pow1 == Power::earth && pow2 == Power::water)
		|| (pow1 == Power::water && pow2 == Power::fire))
	{
		return -1;
	}
	return 1;
}

void System::writeToBinary(std::ofstream& os) const {
	size_t size = market.size();
	os.write((const char*)&size, sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		market[i].writeToBinary(os);
	}

	users.writeToBinary(os);

}
void System::readFromBinary(std::ifstream& is) {
	size_t currentSize = 0;
	is.read((char*)&currentSize, sizeof(size_t));
	market = vector<Superhero>(currentSize);

	for (size_t i = 0; i < currentSize; i++)
	{
		Superhero superhero;
		superhero.readFromBinary(is);
		market.push_back(std::move(superhero));
	}
	is.read((char*)&currentSize, sizeof(size_t));
	for (size_t i = 0; i < currentSize; i++)
	{
		bool isAdmin = true;
		is.read((char*)&isAdmin, sizeof(bool));

		if (isAdmin)
		{
			Admin* admin = new Admin;
			admin->readFromBinary(is);
			users.add(admin);
		}
		else
		{
			Player* player = new Player;
			player->readFromBinary(is);

			size_t superheroesSize = 0;
			is.read((char*)&superheroesSize, sizeof(size_t));
			for (size_t j = 0; j < superheroesSize; j++)
			{
				String currentNickname;
				currentNickname.readFromBinary(is);

				int idx = findSuperhero(currentNickname);
				player->addSuperhero(&market[idx]);
			}
			users.add(player);
		}
	}
}

void writeUsersToBinary(const User* users, size_t size, std::ofstream& os) {
	os.write((const char*)&size, sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		users[i].writeToBinary(os);
	}
}

size_t System::marketSize() const {
	return market.size();
}

vector<Player*> System::players() {
	vector<Player*> result;
	for (size_t i = 0; i < users.size(); i++)
	{
		if (users[i]->isAdmin() == false)
		{
			result.push_back(static_cast<Player*>(users[i]));
		}
	}
	return result;
}

void System::profile() const {
	current->print(true);
}