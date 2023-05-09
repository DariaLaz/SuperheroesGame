#include "User.h"
#include "String.h"

User::User(const String& firstName,
	const String& lastName,
	const String& password,
	const String& nickname) : User(firstName.c_str(), lastName.c_str(), password.c_str(), nickname.c_str()) {}
User::User(const char* firstName,
	const char* lastName,
	const char* password,
	const char* nickname) {
	try
	{
		_firstName = firstName;
		_lastName = lastName;
		if (!isValidPass(password))
		{
			throw std::logic_error("Invalid password");
		}
		if (!isUnique(nickname))
		{
			throw std::logic_error("Invalid nickname");
		}
		_password = password;
		_nickname = nickname;
	}
	catch (const std::logic_error&)
	{
		throw;
	}
}
const String& User::firstName() const {
	return _firstName;
}
const String& User::lastName() const{
	return _lastName;
}
const String& User::username() const{
	return _nickname;
}

bool User::isValidPass(const char* password) const {
	bool isUpcase = false;
	bool isDowncase = false;
	bool isDigit = false;
	while (*password)
	{
		if (isUpperCase(*password)){
			isUpcase = true;
		}
		else if (isDownCase(*password)) {
			isDowncase = true;
		}
		else if (this->isDigit(*password)) {
			isDigit = true;
		}
		password++;
	}
	return isUpcase && isDowncase && isDigit;
}
bool User::isValidPass(const String& password) const {
	return isValidPass(password.c_str());
}

bool User::isUpperCase(char ch) const {
	return ch >= 'A' && ch <= 'Z';
}
bool User::isDownCase(char ch) const {
	return ch >= 'a' && ch <= 'z';
}
bool User::isDigit(char ch) const {
	return ch >= '0' && ch <= '9';
}

bool User::isUnique(const char* nickname) const {
	return nicknames.constains(nickname);
}
bool User::isUnique(const String& nickname) const {
	return isUnique(nickname);
}

bool User::isPass(const String& pass) const {
	return _password == pass;
}
void User::print(bool isAdmin = false) const {
	std::cout << "+++" << username() << "+++\n";

	if (isAdmin)
	{

	}
}
