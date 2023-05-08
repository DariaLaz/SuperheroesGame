#include "System.h"
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
	double price = 0.0,
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
	if (isAdmin)
	{
		deleteAdminAt(findAdmin(current->nickname()));
	}
	else
	{
		deletePlayerAt(findPlayer(current->nickname()));
	}
	current = nullptr;
}
/*����� ����� ������ �� ���� �� ����� ������ �� ������ ������, � ����� �� �������� ���� ������� ������������� �����,
		� ����� ���� ���������� � ����� ���������� ����(��� ������� ����).*/
void System::printAll() const {
	userCheck();
	for (size_t i = 0; i < _players.size(); i++)
	{
		_players[i].print(isAdmin);
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
		_market[i].print(isAdmin);
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




void System::userCheck() const {
	if (!current)
	{
		throw std::logic_error("There is no logged in user!");
	}
}
void System::adminCheck() const {
	if (!isAdmin)
	{
		throw std::logic_error("Not an admin!");
	}
}
void System::playerCheck() const {
	if (isAdmin || !current)
	{
		throw std::logic_error("Not a player!");
	}
}
