#include "Superhero.h"

vector<String> Superhero::nicknames(8);

Superhero::Superhero(const String& firstName,
					 const String& lastName,
					 const String& nickname,
					 const Power& power,
					 size_t strenght,
					 double price,
					 const Mode& mode) 
	: Superhero(firstName.c_str(), lastName.c_str(), nickname.c_str(), power, strenght, price, mode) {}

Superhero::Superhero(const char* firstName,
	const char* lastName,
	const char* nickname,
	const Power& power,
	size_t strenght,
	double price,
	const Mode& mode) {
	if (!isUnique(nickname))
	{
		throw std::logic_error("Invalid nickname");
	}
	_firstName = firstName;
	_lastName = lastName;
	_nickname = nickname;
	_power = power;
	_strenght = strenght;
	_price = price;
	_mode = mode;
	nicknames.push_back(nickname);
}

const String& Superhero::firstName() const {
	return _firstName;
}
const String& Superhero::lastName() const {
	return _lastName;
}
const String& Superhero::nickname() const {
	return _nickname;
}
const Power& Superhero::power() const {
	return _power;
}
size_t Superhero::strenght() const {
	return _strenght;
}
double Superhero::price() const {
	return _price;
}
Mode Superhero::mode() const {
	return _mode;
}

bool Superhero::isUnique(const String& nickname) const {
	return !nicknames.constains(nickname);
}




void Superhero::setMode(const Mode& mode) {
	_mode = mode;
}

void Superhero::print(bool isAdmin) const {
	if (_mode != Mode::notBought || isAdmin)
	{
		std::cout << nickname() << std::endl;
	}
}