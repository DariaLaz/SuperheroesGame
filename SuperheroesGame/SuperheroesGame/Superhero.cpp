#include "Superhero.h"

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
	return nicknames.constains(nickname);
}

int Superhero::attack(Superhero* other) {
	size_t attackerPoints = strenght();
	size_t defenderPoints = other->strenght();

	int cmp = comparePower(power(), other->power());

	if (cmp < 0)
	{
		defenderPoints *= 2;
	}
	else if (cmp > 0)
	{
		attackerPoints *= 2;
	}

	if (attackerPoints > defenderPoints)
	{
		size_t diff = abs((int)(strenght() - other->strenght()));
		if (other->mode() == Mode::defence)
		{
			return 0;
		}
		owner->winModey(diff);
		other->owner->loseMoney(diff);
		return diff;
	}
	else if (attackerPoints == defenderPoints)
	{
		//k
		size_t lose = rand() % strenght();
		owner->loseMoney(lose);
		return -lose;
	}
	else
	{
		size_t diff = abs((int)(strenght() - strenght()));

		//z
		owner->loseMoney(diff);
		other->owner->winMoney((rand() % (2 * diff)) + diff);

		return -diff;
	}
}

int Superhero::comparePower(const Power& pow1, const Power& pow2) const {
	if ((pow1 == Power::fire && pow2 == Power::earth)
		|| (pow1 == Power::earth && pow2 == Power::water)
		|| (pow1 == Power::water && pow2 == Power::fire))
	{
		return -1;
	}
	return 1;
}


