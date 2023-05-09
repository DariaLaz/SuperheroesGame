#pragma once
#include "String.h"
#include "vector.hpp"

class User
{
	String _firstName;
	String _lastName;
	String _nickname;
	String _password;

public:
	static vector<String> nicknames;


	User() = default;
	User(const String& firstName,
		const String& lastName,
		const String& password,
		const String& nickname);
	User(const char* firstName,
		const char* lastName,
		const char* password,
		const char* nickname);
	const String& firstName() const;
	const String& lastName() const;
	const String& username() const;

	bool isPass(const String& pass) const;

	virtual void print(bool isAdmin = false) const;

private:
	bool isValidPass(const char* password) const;
	bool isValidPass(const String& password) const;
	bool isUpperCase(char ch) const;
	bool isDownCase(char ch) const;
	bool isDigit(char ch) const;
	//bool isUnique(const char* nickname) const;
	bool isUnique(const String& nickname) const;
	//bool isUnique(String&& nickname) const;
};

