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
	Power _power;
	size_t _strenght;
	double _price;
	Mode _mode;

	static vector<String> nicknames;
public:
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
private:
	bool isUnique(const String& nickname) const;

};

