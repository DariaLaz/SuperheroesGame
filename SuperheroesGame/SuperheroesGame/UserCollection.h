#pragma once
#include "User.h"
#include "Player.h"


class UserCollection
{
	vector<User*> users;
	size_t _size = 0;

public:
	UserCollection();
	UserCollection(const UserCollection& other);
	UserCollection& operator=(const UserCollection& other);
	UserCollection(UserCollection&& other);
	UserCollection& operator=(UserCollection&& other);

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
private:
	void copyFrom(const UserCollection& other);
	void moveFrom(UserCollection&& other);
	void free();
};

