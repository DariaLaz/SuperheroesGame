#pragma once
#include "String.h"
#include "vector.hpp"
#include "Helpers.h"

class User
{
	String _firstName;
	String _lastName;
	String _username;
	String _password;
protected:
	//Usernames of existing users
	static vector<String> usernames;
public:
	//Constructors:
	User() = default;
	User(const String& firstName,
		const String& lastName,
		const String& password,
		const String& nickname);
	User(const char* firstName,
		const char* lastName,
		const char* password,
		const char* nickname);
	User(String&& firstName,
		String&& lastName,
		String&& password,
		String&& nickname);
	virtual ~User() = default;
	//Getters
	const String& firstName() const;
	const String& lastName() const;
	const String& username() const;

	//Checks if the password is correct
	bool isPass(const String& pass) const;

	//Print user
	virtual void print(bool isAdmin) const = 0;

	//Write user in binary file
	virtual void writeToBinary(std::ofstream& os) const;
	//Read user from binary file
	virtual void readFromBinary(std::ifstream& is);

	//Returns copy of the object
	virtual User* clone() const = 0;

	virtual bool isAdmin() const = 0;
private:
	//checks if the given username is unique (does not exist user with the same username)
	bool isUnique(const String& username) const;

	void setUsername(const char* name);
	void setUsername(const String& name);
	void setUsername(String&& name);
};
//Checks if the password is valid (contains at least one lowercase letter, uppercase letter and digit)
bool isValidPass(const char* password);
bool isValidPass(const String& password);

