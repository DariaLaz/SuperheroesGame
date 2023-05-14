#include "System.h"

System::System() {

	std::ifstream ifs(FileConstants::FILE_NAME, std::ios::in | std::ios::binary);
	if (!ifs.is_open())
		throw std::logic_error("Can not open the file!");

	readFromBinary(ifs);
	ifs.close();
	if (_admins.size() == 0)
	{
		User admin("Admin", "Admin", "Pass1", "admin");
		_admins.push_back(std::move(admin));
	}
}

//ADMIN FUNCTIONS
//����� ������������� ������ �� ���� �� ������ ���� �������������� � ������ � ���������.
void System::addAdmin(const User& user) {
	adminCheck();
	_admins.push_back(user);
}
void System::addAdmin(User&& user) {
	adminCheck();
	_admins.push_back(std::move(user));
}
void System::addAdmin(const char* firstName,
	const char* lastName,
	const char* nickname,
	const char* password) {
	adminCheck();
	User user(firstName, lastName, password, nickname);
	_admins.push_back(std::move(user));
}
void System::addAdmin(const String& firstName,
	const String& lastName,
	const String& nickname,
	const String& password) {
	adminCheck();

	User user(firstName, lastName, password, nickname);

	_admins.push_back(std::move(user));
	User::usernames.push_back(nickname);
}
void System::addPlayer(const Player& player) {
	adminCheck();

	_players.push_back(player);
	User::usernames.push_back(player.username());

}
void System::addPlayer(Player&& player) {
	adminCheck();
	User::usernames.push_back(player.username());
	_players.push_back(std::move(player));
}
void System::addPlayer(const char* firstName,
	const char* lastName,
	const char* username,
	const char* password,
	double money) {
	adminCheck();

	Player player(firstName, lastName, username, password, money);
	_players.push_back(std::move(player));
	User::usernames.push_back(username);

}
void System::addPlayer(const String& firstName,
	const String& lastName,
	const String& username,
	const String& password,
	double money) {
	adminCheck();

	Player player(firstName, lastName, password, username, money);
	_players.push_back(std::move(player));
	User::usernames.push_back(username);
}

//����� ������������� ������ �� ���� �� ������� ������� �� ������.
void System::deletePlayer(const String& nickname) {
	adminCheck();

	int idx = findPlayer(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	deletePlayerAt(idx);
}

//����� ������������� ������ �� ��� ����� �� ����� ������ ������������ �� ����� ���������� � ������� 
//�������(��� ����������������, ���� ������������� ���� �� ����� ���� ������� � ������ �� ���� �������������) .
void System::printInfo(const String& nickname) const {
	adminCheck();

	int idx = findPlayer(nickname);
	if (idx >= 0)
	{
		_players[idx].print(true);
		return;
	}
	idx = findAdmin(nickname);
	if (idx >= 0)
	{
		_admins[idx].print(true);
		return;
	}
	throw std::out_of_range("Invalid nickname!");
}

//����� ������������� ������ �� ���� �� ������ ���� ���������� ��� ��������. � ������, �� �� �������� ���� ������� ����������, ��������������� ��� � ��������� �� ������ �� ������ ���� 3 ����������. ��������������� ������ �� ���� �� ����� ������ ����������, ����� �� ���� ��������� � �� ���� �� ������ ���� �� ��� �� ��������, ��� �� ����� �� ������ ���.
void System::addSuperhero(const Superhero& superhero) {
	adminCheck();

	_market.push_back(superhero);
}
void System::addSuperhero(Superhero&& superhero) {
	adminCheck();

	_market.push_back(std::move(superhero));
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
	_market.push_back(std::move(hero));
}
void System::resurrect(const String& nickname) {
	adminCheck();

	int idx = findSuperhero(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	if (_market[idx].mode() != Mode::dead)
	{
		throw std::logic_error("This superhero already exists!");
	}
	_market[idx].setMode(Mode::notBought);
}

vector<Superhero> System::market() const {
	return _market;
}




//PLAYER FUNCTIONS
//����� ����� ������ �� ���� �� ������� ������� ��.
void System::deleteMe() {
	userCheck();
	if (_isAdmin)
	{
		if (_admins.size() == 1)
		{
			throw std::logic_error("You are the only admin and cannot be deleted!");
		}
		deleteAdminAt(findAdmin(current->username()));
	}
	else
	{
		deletePlayerAt(findPlayer(current->username()));
	}
	current = nullptr;
}
/*����� ����� ������ �� ���� �� ����� ������ �� ������ ������, � ����� �� �������� ���� ������� ������������� �����,
		� ����� ���� ���������� � ����� ���������� ����(��� ������� ����).*/
void System::printPlayers() const {
	userCheck();
	for (size_t i = 0; i < _players.size(); i++)
	{
		_players[i].print(_isAdmin);
	}
} 
void System::printAdmins() const {
	userCheck();
	if (!_isAdmin)
	{
		return;
	}
	for (size_t i = 0; i < _players.size(); i++)
	{
		_admins[i].print();
	}
}
//����� ����� ������ �� ���� �� ����� ���������� ���������
void System::results() {
	sort();
	printPlayers();
}
//��������������� ������ �� ���� �� ����� ������ ����������, ����� �� ���� ��������� � �� ���� �� ������ ���� �� ��� �� ��������, 
//��� �� ����� �� ������ ���.
//����� ����� ������ �� ���� �� ����� ������ �� ���������� (����� � ��� �� ������ ������) � ��� ������� �� ������ ����� ����������. 
//���� ������������ ����������� ������ �� ������� �� ������. �� � ��������� ��������� �� ���� � ��� ����������, 
//����� ���� ����������� �� ���� ����� ���� � ���� ��������� ����� �������� ������.
void System::printMarket() const {
	userCheck();

	for (size_t i = 0; i < _market.size(); i++)
	{
		if (_market[i].mode() == Mode::notBought || (_isAdmin && _market[i].mode() == Mode::dead))
		{
			_market[i].print(_isAdmin);
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
	if (idx < 0 || _market[idx].mode() != Mode::notBought)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	((Player*)current)->addSuperhero(&_market[idx]);
}
//����� ����� ������ �� ���� �� ������� ������ �� ���� ���������� �� ����� ����������.
int System::attack(const String& nickname, const String& userNickname, const String& heroNickname) {
	playerCheck();
	Player& attacker = *((Player*)current);
	Player* defender = nullptr;
	
	if (userNickname == nullptr)
	{
		size_t superheroIdx = findSuperhero(heroNickname);
		if (superheroIdx == -1)
		{
			throw std::out_of_range("Invalid nickname!");
		}
		if (_market[superheroIdx].mode() == Mode::notBought || _market[superheroIdx].mode() == Mode::dead)
		{
			throw std::logic_error("Invalid nickname!");
		}
		for (size_t i = 0; i < _players.size(); i++)
		{
			size_t currSize = _players[i].superheroesCount();
			for (size_t j = 0; j < currSize; j++)
			{
				if (_players[i].getHeroAt(j) == &_market[superheroIdx])
				{
					defender = &_players[i];
					break;
				}
			}
			if (defender != nullptr)
			{
				break;
			}
		}
	}
	else
	{
		int idx = findPlayer(userNickname);
		if (idx < 0)
		{
			throw std::out_of_range("Invalid username!");
		}
		defender = &_players[idx];
	}
	Superhero& attackHero = *attacker.getHeroAt(attacker.findHero(nickname));

	if (defender->superheroesCount() == 0)
	{
		defender->loseMoney(attackHero.strenght());
		size_t win = rand() % (2 * attackHero.strenght());
		attacker.winMoney(win);

		return win;
	}
	Superhero* defendHero = nullptr;
	if (heroNickname == nullptr)
	{
		defendHero = defender->getHeroAt(rand() % defender->superheroesCount());
	}
	defendHero = defender->getHeroAt(defender->findHero(heroNickname));

	size_t attackerPoints = attackHero.strenght();
	size_t defenderPoints = defendHero->strenght();

	int cmp = comparePower(attackHero.power(), defendHero->power());
	if (cmp < 0)
	{
		defenderPoints *= 2;
	}
	else if (cmp > 0)
	{
		attackerPoints *= 2;
	}

	if (defenderPoints == attackerPoints)
	{
		size_t lose = rand() % attackHero.strenght();
		attacker.loseMoney(lose);
		return lose * (-1);
	}
	else if (defenderPoints < attackerPoints) {
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
		size_t diff = attackerPoints - defenderPoints;
		defender->winMoney(rand() % (2 * diff));
		attacker.loseMoney(2 * diff);
		attackHero.setMode(Mode::dead);
		attacker.removeSuperhero(&attackHero);
		return diff * (-2);
	}
}

void System::login(const String& username, const String& password) {
	for (size_t i = 0; i < _admins.size(); i++)
	{
		if (_admins[i].username() == username && _admins[i].isPass(password))
		{
			_isAdmin = true;
			current = &_admins[i];
			return;
		}
	}
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (_players[i].username() == username && _players[i].isPass(password))
		{
			_isAdmin = false;
			current = &_players[i];
			return;
		}
	}
	throw std::logic_error("Invalid username ot password");
}

void System::logout() {
	_isAdmin = false;
	current = nullptr;
}
bool System::isLogged() const {
	return current != nullptr;
}
bool System::isAdmin() const {
	return _isAdmin;
}

void System::deletePlayerAt(size_t idx) {
	_players.erase(idx);
}
void System::deleteAdminAt(size_t idx) {
	_admins.erase(idx);
}

int System::findPlayer(const String& nickname) const {
	for (size_t i = 0; i < _players.size(); i++)
	{
		if (_players[i].username() == nickname)
		{
			return i;
		}
	}
	return -1;
}
int System::findAdmin(const String& nickname) const {
	for (size_t i = 0; i < _admins.size(); i++)
	{
		if (_admins[i].username() == nickname)
		{
			return i;
		}
	}
	return -1;
}
int System::findSuperhero(const String& nickname) const {
	for (size_t i = 0; i < _market.size(); i++)
	{
		if (_market[i].nickname() == nickname)
		{
			return i;
		}
	}
	return -1;
}
int System::findSuperhero(const char* nickname) const {
	for (size_t i = 0; i < _market.size(); i++)
	{
		if (strcmp(_market[i].nickname().c_str(), nickname) == 0)
		{
			return i;
		}
	}
	return -1;
}

void System::sort() {
	size_t size = _players.size();
	for (size_t i = 0; i < size; i++)
	{
		size_t maxIndex = i;
		for (size_t j = i; j < size; j++)
		{
			if (_players[maxIndex].money() < _players[j].money())
			{
				maxIndex = j;
			}
		}
		if (maxIndex != i)
		{
			swap(_players[i], _players[maxIndex]);
		}
	}
}

void System::userCheck() const {
	if (!current)
	{
		throw std::logic_error("There is no logged in user!");
	}
}
void System::adminCheck() const {
	if (!_isAdmin)
	{
		throw std::logic_error("Not an admin!");
	}
}
void System::playerCheck() const {
	if (_isAdmin || !current)
	{
		throw std::logic_error("Not a player!");
	}
}

int System::comparePower(const Power& pow1, const Power& pow2) const {
	if ((pow1 == Power::fire && pow2 == Power::earth)
		|| (pow1 == Power::earth && pow2 == Power::water)
		|| (pow1 == Power::water && pow2 == Power::fire))
	{
		return -1;
	}
	return 1;
}

void System::writeToBinary(std::ofstream& os) const {
	writeUsersToBinary(_admins.data(), _admins.size(), os);

	size_t size = _market.size();
	os.write((const char*)&size, sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		_market[i].writeToBinary(os);
	}

	writeUsersToBinary(_players.data(), _players.size(), os);

}
void System::readFromBinary(std::ifstream& is) {
	size_t currentSize = 0;
	is.read((char*)&currentSize, sizeof(size_t));
	_admins = vector<User>(currentSize);
	for (size_t i = 0; i < currentSize; i++)
	{
		User user;
		user.readFromBinary(is);
		_admins.push_back(std::move(user));
	}

	is.read((char*)&currentSize, sizeof(size_t));
	_market = vector<Superhero>(currentSize);

	for (size_t i = 0; i < currentSize; i++)
	{
		Superhero superhero;
		superhero.readFromBinary(is);
		_market.push_back(std::move(superhero));
	}

	is.read((char*)&currentSize, sizeof(size_t));
	_players = vector<Player>(currentSize);
	for (size_t i = 0; i < currentSize; i++)
	{
		Player player;
		player.readFromBinary(is);
		_players.push_back(std::move(player));


		size_t superheroesSize = 0;
		is.read((char*)&superheroesSize, sizeof(size_t));
		for (size_t j = 0; j < superheroesSize; j++)
		{
			String currentNickname;
			currentNickname.readFromBinary(is);

			int idx = findSuperhero(currentNickname);
			_players[i].addSuperhero(&_market[idx]);
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
