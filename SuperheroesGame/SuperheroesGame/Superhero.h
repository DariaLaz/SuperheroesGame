#pragma once
#include "String.h"
#include "Power.h"
#include "Mode.h"
#include "vector.hpp"

class Superhero
{
	String _firstName;
	String _lastName;
	String _nickname;
	Power _power = Power::earth;
	size_t _strenght;
	double _price;
	Mode _mode = Mode::notBought;

	static vector<String> nicknames;
public:
	Superhero() = default;
	Superhero(const String& firstName,
			  const String& lastName,
			  const String& nickname,
			  const Power& power,
			  size_t strenght,
			  double price,
			  const Mode& mode = Mode::notBought);
	Superhero(const char* firstName,
			  const char* lastName,
			  const char* nickname,
			  const Power& power,
			  size_t strenght,
			  double price,
			  const Mode& mode = Mode::notBought);
	const String& firstName() const;
	const String& lastName() const;
	const String& nickname() const;
	const Power& power() const;
	size_t strenght() const;
	double price() const;
	Mode mode() const;

	void setMode(const Mode&);
	void print(bool isAdmin) const;

	void writeToBinary(std::ofstream& os) const;
	void readFromBinary(std::ifstream& is);
private:
	bool isUnique(const String& nickname) const;
	

};
String getMode(const Mode& mode);
String getPower(const Power& pow);
Mode getMode(const String& mode);
Power getPower(const String& pow);

std::ostream& operator<<(std::ostream& os, const Superhero& str);

