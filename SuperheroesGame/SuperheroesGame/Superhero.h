#pragma once
#include "String.h"
#include "Power.h"
#include "Mode.h"

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
	const String& firstName() const;
	const String& lastName() const;
	const String& nickname() const;
	const Power& power() const;
	size_t strenght() const;
	double price() const;
	Mode mode() const;
};

