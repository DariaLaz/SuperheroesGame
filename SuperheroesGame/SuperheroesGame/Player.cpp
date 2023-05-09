#include "Player.h"

double Player::money() const {
	return _money;
}

Player::Player(const String& firstName,
	const String& lastName,
	const String& password,
	const String& nickname,
	double money) {

}
Player::Player(const char* firstName,
	const char* lastName,
	const char* password,
	const char* nickname,
	double money) {

}
double Player::money() const {

}
size_t Player::find(const char*) const {

}
Superhero* Player::getAt(size_t) {

}

void Player::print(bool isAdmin = false) const {
	std::cout << "+++" << username() << "+++\n";
	std::cout << "-- ($" << money() << ") --\n";
	for (size_t i = 0; i < superheroes.size(); i++)
	{
		std::cout << "- " << superheroes[i]->nickname() << "\n";
	}
}
void Player::changeMode(const String& nickname, const Mode& mode) {
	changeMode(nickname.c_str(), mode);
}
void Player::changeMode(const char* nickname, const Mode& mode) {
	int idx = findSuperhero(nickname);
	if (idx < 0)
	{
		throw std::out_of_range("Invalid nickname!");
	}
	changeMode(superheroes[idx], mode);
}
void Player::changeMode(Superhero* superhero, const Mode& mode) {
	if (superhero->owner() != this)
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