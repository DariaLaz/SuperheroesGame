#include "System.h"

System::System() {
	User admin("Admin", "Admin", "Pass1", "admin");

	_admins.push_back(std::move(admin));
}

//ADMIN FUNCTIONS
//Всеки администратор трябва да може да добавя нови администратори и играчи в системата.
void System::addAdmin(const User& user) {
	adminCheck();
	_admins.push_back(user);
	User::nicknames.push_back(user.username());
}
void System::addAdmin(User&& user) {
	adminCheck();
	User::nicknames.push_back(user.username());
	_admins.push_back(std::move(user));
}
void System::addAdmin(const char* firstName,
	const char* lastName,
	const char* nickname,
	const char* password) {
	adminCheck();
	User user(firstName, lastName, password, nickname);
	_admins.push_back(std::move(user));
	User::nicknames.push_back(nickname);
}
void System::addAdmin(const String& firstName,
	const String& lastName,
	const String& nickname,
	const String& password) {
	adminCheck();

	User user(firstName, lastName, password, nickname);

	_admins.push_back(std::move(user));
	User::nicknames.push_back(nickname);
}
void System::addPlayer(const Player& player) {
	adminCheck();

	_players.push_back(player);
	User::nicknames.push_back(player.username());

}
void System::addPlayer(Player&& player) {
	adminCheck();
	User::nicknames.push_back(player.username());
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
	User::nicknames.push_back(username);

}
void System::addPlayer(const String& firstName,
	const String& lastName,
	const String& username,
	const String& password,
	double money) {
	adminCheck();

	Player player(firstName, lastName, password, username, money);
	_players.push_back(std::move(player));
	User::nicknames.push_back(username);
}

//Всеки администратор трябва да може да изтрива профили на играчи.
void System::deletePlayer(const String& nickname) {
	adminCheck();

	int idx = findPlayer(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	deletePlayerAt(idx);
}

//Всеки администратор трябва да има права да вижда цялата информацията за всеки потребител и неговия 
//прогрес(без администраторите, един администратор може да вижда само имената и имейла на друг администратор) .
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

//Всеки администратор трябва да може да добавя нови супергерои към “пазара”. В случай, че на “пазара” няма никакви супергерои, администраторът още с влизането си трябва да добави поне 3 супергероя. Администраторът трябва да може да вижда всички супергерои, които са били продадени и да може да избере един от тях за добавяне, ако не желае да добавя нов.
void System::addToMarket(const Superhero& superhero) {
	adminCheck();

	_market.push_back(superhero);
}
void System::addToMarket(Superhero&& superhero) {
	adminCheck();

	_market.push_back(std::move(superhero));
}
void System::addToMarket(const String& firstName,
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
//Всеки играч трябва да може да изтрива профила си.
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
/*Всеки играч трябва да може да вижда списък от всички играчи, в който са записани само техните потребителски имена,
		с колко пари разполагат и какви супергерои имат(без тяхната сила).*/
void System::printAll() const {
	userCheck();
	for (size_t i = 0; i < _players.size(); i++)
	{
		_players[i].print(_isAdmin);
	}
} 
//Всеки играч трябва да може да вижда моментното класиране
void System::results() {
	sort();
	printAll();
}
//Администраторът трябва да може да вижда всички супергерои, които са били продадени и да може да избере един от тях за добавяне, 
//ако не желае да добавя нов.
//Всеки играч трябва да може да вижда пазара от супергерои (който е общ за всички играчи) и при желание да закупи някой супергерой. 
//След закупуването супергероят трябва да изчезне от пазара. Не е позволено дублиране на един и същ супергерой, 
//както като собственост на един играч така и като дублиране между различни играчи.
void System::printMarket() const {
	userCheck();

	for (size_t i = 0; i < _market.size(); i++)
	{
		if (_market[i].mode() == Mode::notBought || (_isAdmin && _market[i].mode() == Mode::dead))
		{
			std::cout << " -> " << _market[i] << std::endl;
		}
	}
}
//Всеки играч трябва да може да променя позицията на героите си от атакуваща в дефанзивна и обратното.
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
//Всеки играч трябва да може да нападне избран от него супергерой на даден потребител.
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
				if (_players[i].getAt(j) == &_market[superheroIdx])
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
	Superhero& attackHero = *attacker.getAt(attacker.find(nickname));

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
		defendHero = defender->getAt(rand() % defender->superheroesCount());
	}
	defendHero = defender->getAt(defender->find(heroNickname));

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
