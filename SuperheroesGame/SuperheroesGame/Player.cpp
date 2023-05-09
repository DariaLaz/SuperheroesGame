#include "Player.h"

double Player::money() const {
	return _money;
}

Player::Player(const String& firstName,
	const String& lastName,
	const String& password,
	const String& nickname,
	double money) :User(firstName, lastName, password, nickname) {
	_money = money;
}
Player::Player(const char* firstName,
	const char* lastName,
	const char* password,
	const char* nickname,
	double money) :User(firstName, lastName, password, nickname) {
	_money = money;
}
int Player::find(const char* nickname) const {
	for (size_t i = 0; i < superheroes.size(); i++)
	{
		if (superheroes[i]->nickname() == nickname)
		{
			return i;
		}
	}
	return -1;
}
Superhero* Player::getAt(size_t idx) {
	return superheroes[idx];
}
size_t Player::superheroesCount() const {
	return superheroes.size();
}


void Player::print(bool isAdmin) const {
	std::cout << "+++" << username() << "+++\n";
	std::cout << "-- ($" << _money << ") --\n";
	for (size_t i = 0; i < superheroes.size(); i++)
	{
		std::cout << "- " << superheroes[i]->nickname() << "\n";
	}
}
void Player::changeMode(const String& nickname, const Mode& mode) {
	changeMode(nickname.c_str(), mode);
}
void Player::changeMode(const char* nickname, const Mode& mode) {
	int idx = find(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	changeMode(superheroes[idx], mode);
}
void Player::changeMode(Superhero* superhero, const Mode& mode) {
	if (!superheroes.constains(superhero))
	{
		throw std::logic_error("Access error!");
	}
	superhero->setMode(mode);
}


void Player::addSuperhero(Superhero* superhero) {
	superhero->setMode(Mode::defence);
	superheroes.push_back(superhero);
	loseMoney(superhero->price());
} 
void Player::loseMoney(double money) {
	if (_money < money )
	{
		_money = 0;
	}
	else
	{
		_money -= money;
	}
}
void Player::winMoney(double money) {
	_money += money;
}

void Player::removeSuperhero(Superhero* superhero) {
	int idx = superheroes.find(superhero);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid superhero!");
	}
	superheroes.erase(idx);
}