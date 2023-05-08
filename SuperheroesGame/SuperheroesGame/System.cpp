#include "System.h"
//ADMIN FUNCTIONS
//Всеки администратор трябва да може да добавя нови администратори и играчи в системата.
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
	_market.push_back(superhero);
}
void System::addToMarket(Superhero&& superhero) {
	_market.push_back(std::move(superhero));
}
void System::addToMarket(const String& firstName,
	const String& lastName,
	const String& nickname,
	const Power& power,
	size_t strenght,
	double price = 0.0,
	Mode mode = Mode::notBought) {
	Superhero hero(firstName, lastName, nickname, power, strenght, price, mode);
	_market.push_back(std::move(hero));
}
vector<Superhero> System::market() const {
	return _market;
}
void System::printMarket() const {
	for (size_t i = 0; i < _market.size(); i++)
	{
		_market[i].print(true);
	}
}

void System::adminCheck() const {
	if (!isAdmin)
	{
		throw std::logic_error("Not an admin!");
	}
}

//PLAYER FUNCTIONS
//Всеки играч трябва да може да изтрива профила си.
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
void System::userCheck() const {
	if (!current)
	{
		throw std::logic_error("There is no loged in user!");
	}
}
