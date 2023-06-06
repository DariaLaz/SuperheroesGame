#pragma once
#include "User.h"
#include "Admin.h"
#include "Player.h"


class UserCollection
{
	vector<User*> users;
	size_t _size = 0;

public:
	UserCollection();
	UserCollection(const UserCollection& other);

	explicit UserCollection(size_t capacity);
	~UserCollection(); 

	size_t add(bool isAdmin);
	size_t add(User* user);


	int find(const String& username) const;

	bool removeAt(size_t idx);

	size_t size() const;
	size_t adminsCount() const;

	User* operator[](size_t idx);
	const User* operator[](size_t idx) const;

	void writeToBinary(std::ofstream& os) const;
};

