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
void Superhero::print() const {
	std::cout << " ->" << _nickname << " - " << getMode(_mode) << std::endl;
}



void Superhero::setMode(const Mode& mode) {
	_mode = mode;
}

void Superhero::writeToBinary(std::ofstream& os) const {
	if (!os.is_open())
		throw std::logic_error("Can not open the file!");

	_firstName.writeToBinary(os);
	_lastName.writeToBinary(os);
	_nickname.writeToBinary(os);
	String power = getPower(_power);
	power.writeToBinary(os);
	os.write((const char*)&_strenght, sizeof(size_t));
	os.write((const char*)&_price, sizeof(double));
	String mode = getMode(_mode);
	mode.writeToBinary(os);
}
void Superhero::readFromBinary(std::ifstream& is) {
	if (!is.is_open())
		throw std::logic_error("Can not open the file!");

	_firstName.readFromBinary(is);
	_lastName.readFromBinary(is);
	_nickname.readFromBinary(is);
	String power;
	power.readFromBinary(is);
	is.read((char*)&_strenght, sizeof(size_t));
	is.read((char*)&_price, sizeof(double));
	String mode;
	mode.readFromBinary(is);

	_power = getPower(power);
	_mode = getMode(mode);
}


std::ostream& operator<<(std::ostream& os, const Superhero& sh) {
	return os << sh.firstName() << ' ' << sh.lastName() << sh.nickname() << getPower(sh.power()) << sh.strenght() << sh.price() << getMode(sh.mode());
}

String getMode(const Mode& mode) {
	switch (mode)
	{
	case Mode::attack: return "ATTACK";
	case Mode::dead: return "DEAD";
	case Mode::defence: return "DEFENCE";
	case Mode::notBought: return "NOT BOUGHT";

	default:
		break;
	}
}
Mode getMode(const String& mode) {
	if (mode == "ATTACK")
	{
		return Mode::attack;
	}
	if (mode == "DEAD")
	{
		return Mode::dead;
	}
	if (mode == "DEFENCE")
	{
		return Mode::defence;
	}
	if (mode == "NOT BOUGHT")
	{
		return Mode::notBought;
	}
	throw std::invalid_argument("Invalid mode!");

}
String getPower(const Power& pow) {
	switch (pow)
	{
	case Power::earth: return "EARTH";
	case Power::fire: return "FIRE";
	case Power::water: return "WATER";
	default:
		break;
	}
}
Power getPower(const String& pow) {
	if (pow == "EARTH")
	{
		return Power::earth;
	}
	if (pow == "FIRE")
	{
		return Power::fire;
	}
	if (pow == "WATER")
	{
		return Power::water;
	}
	throw std::invalid_argument("Invalid power!");
}
