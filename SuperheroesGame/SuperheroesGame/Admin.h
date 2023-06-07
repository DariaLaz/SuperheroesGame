#pragma once
#include "User.h"
class Admin : public User
{
public:
	//Constructors:
	Admin() = default;
	Admin(const String& firstName, const String& lastName, const String& username, const String& password)
		:User(firstName, lastName, password, username){}
	//Print current object's data
	void print(bool isAdmin) const override;
	//Return a copy
	User* clone() const override;
	//Always true
	bool isAdmin() const override;
};

