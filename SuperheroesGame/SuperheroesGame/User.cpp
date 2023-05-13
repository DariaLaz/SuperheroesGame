#include "User.h"
#include "String.h"

vector<String> User::nicknames(8);

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
		_username = nickname;
		nicknames.push_back(nickname);
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
	return _username;
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


bool User::isUnique(const String& nickname) const {
	return !nicknames.constains(nickname);
}

bool User::isPass(const String& pass) const {
	return _password == pass;
}
void User::print(bool isAdmin) const {
	std::cout << "+++" << username() << " (admin) " << "+++\n";
}

void User::writeToBinary(std::ofstream& os) const {
	if (!os.is_open())
		throw std::logic_error("Can not open the file!");

	_firstName.writeToBinary(os);
	_lastName.writeToBinary(os);
	_username.writeToBinary(os);
	_password.writeToBinary(os);
}
void User::readFromBinary(std::ifstream& is) {
	if (!is.is_open())
		throw std::logic_error("Can not open the file!");

	_firstName.readFromBinary(is);
	_lastName.readFromBinary(is);
	_username.readFromBinary(is);
	_password.readFromBinary(is);
}
