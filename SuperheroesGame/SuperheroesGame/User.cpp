#include "User.h"
#include "String.h"

vector<String> User::usernames(8);

User::User(const String& firstName,
	const String& lastName,
	const String& password,
	const String& nickname) {
	try
	{
		if (firstName == "" || lastName == "")
		{
			throw std::invalid_argument("Invalid name");
		}
		_firstName = firstName;
		_lastName = lastName;
		if (!isValidPass(password))
		{
			throw std::invalid_argument("Invalid password");
		}
		if (!isUnique(nickname))
		{
			throw std::invalid_argument("Invalid nickname");
		}
		_password = password;
		_username = nickname;
		usernames.push_back(nickname);
	}
	catch (const std::invalid_argument&)
	{
		throw;
	}
}
User::User(const char* firstName,
	const char* lastName,
	const char* password,
	const char* nickname) : User(String(firstName), String(lastName), String(password), String(nickname)) {}
User::User(String&& firstName,
	String&& lastName,
	String&& password,
	String&& username) {
	try
	{
		_firstName = std::move(firstName);
		_lastName = std::move(lastName);
		if (!isValidPass(password))
		{
			throw std::logic_error("Invalid password");
		}
		if (!isUnique(username))
		{
			throw std::logic_error("Invalid nickname");
		}
		_password = std::move(password);
		usernames.push_back(username);
		_username = std::move(username);
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


bool User::isUnique(const String& nickname) const {
	return !usernames.constains(nickname);
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


bool isValidPass(const char* password) {
	bool isUpcase = false;
	bool isDowncase = false;
	bool isDig = false;
	while (*password)
	{
		if (isUpperCase(*password)) {
			isUpcase = true;
		}
		else if (isDownCase(*password)) {
			isDowncase = true;
		}
		else if (isDigit(*password)) {
			isDig = true;
		}
		password++;
	}
	return isUpcase && isDowncase && isDig;
}
bool isValidPass(const String& password) {
	return isValidPass(password.c_str());
}
bool isUpperCase(char ch) {
	return ch >= 'A' && ch <= 'Z';
}
bool isDownCase(char ch) {
	return ch >= 'a' && ch <= 'z';
}
bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}