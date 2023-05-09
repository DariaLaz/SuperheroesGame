#include "System.h"

System::System() {
	addAdmin("Admin", "Admin", "admin", "password");
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
	User user(firstName, lastName, nickname, password);
	_admins.push_back(std::move(user));
}
void System::addAdmin(const String& firstName,
	const String& lastName,
	const String& nickname,
	const String& password) {
	adminCheck();

	User user(firstName, lastName, nickname, password);
	_admins.push_back(std::move(user));
}
void System::addPlayer(const Player& player) {
	adminCheck();

	_players.push_back(player);
}
void System::addPlayer(Player&& player) {
	adminCheck();

	_players.push_back(std::move(player));
}
void System::addPlayer(const char* firstName,
	const char* lastName,
	const char* nickname,
	const char* password,
	double money) {
	adminCheck();

	Player player(firstName, lastName, nickname, password, money);
	_players.push_back(std::move(player));
}
void System::addPlayer(const String& firstName,
	const String& lastName,
	const String& nickname,
	const String& password,
	double money) {
	adminCheck();

	Player player(firstName, lastName, nickname, password, money);
	_players.push_back(std::move(player));
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
	Mode mode = Mode::notBought) {
	adminCheck();
	Superhero hero(firstName, lastName, nickname, power, strenght, price, mode);
	_market.push_back(std::move(hero));
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
void System::printAll() const {
	userCheck();
	for (size_t i = 0; i < _players.size(); i++)
	{
		_players[i].print(_isAdmin);
	}
} 
//����� ����� ������ �� ���� �� ����� ���������� ���������
void System::results() const {
	//todo
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
		_market[i].print(_isAdmin);
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
	return attack(nickname.c_str(), userNickname.c_str(), heroNickname.c_str());
}
int System::attack(const char* attackerNickname, const char* userNickname, const char* heroNickname) {
	playerCheck();
	int attakerIdx = ((Player*)current)->find(userNickname);
	if (attakerIdx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	Superhero* attacker = ((Player*)current)->getAt(attakerIdx);
	int userIdx = findPlayer(userNickname);
	if (userIdx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	int heroIdx = _players[userIdx].find(heroNickname);
	if (userIdx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	Superhero& defender = *_players[userIdx].getAt(heroIdx);

	int result = attacker->attack(&defender);
	if (result < 0)
	{
		((Player*)current)->removeSuperhero(attacker);
	}
	else
	{
		_players[userIdx].removeSuperhero(&defender);
	}
	return result;
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
