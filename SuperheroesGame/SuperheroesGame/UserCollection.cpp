#include "UserCollection.h"

UserCollection::UserCollection() : UserCollection(8) {}
UserCollection::UserCollection(const UserCollection& other) : users(other.users.capacity()) {
	_size = other._size;
	for (size_t i = 0; i < _size; i++)
	{
		users[i] = other.users[i]->clone();
	}
}

UserCollection::UserCollection(size_t capacity) : users(capacity) {}
UserCollection::~UserCollection() {
	for (size_t i = 0; i < _size; i++)
	{
		delete users[i];
	}
} 

size_t UserCollection::add(bool isAdmin) {
	if (isAdmin)
	{
		users.push_back(new Admin());
	}
	else
	{
		users.push_back(new Player());
	}
	return ++_size;
}
size_t UserCollection::add(User* user) {
	users.push_back(user);
	return ++_size;
}

int UserCollection::find(const String& username) const {
	for (size_t i = 0; i < _size; i++)
	{
		if (users[i]->username() == username)
		{
			return i;
		}
	}
	return -1;
}
bool UserCollection::removeAt(size_t idx) {
	if (idx >= _size)
	{
		throw std::out_of_range("Invalid index");
	}
	delete users[idx];
	users.erase(idx);
}

void UserCollection::writeToBinary(std::ofstream& os) const {
	os.write((const char*)&_size, sizeof(size_t));
	for (size_t i = 0; i < _size; i++)
	{
		os.write((const char*)users[i]->isAdmin(), sizeof(bool));
		users[i]->writeToBinary(os);
	}
}

size_t UserCollection::size() const {
	return _size;
}
size_t UserCollection::adminsCount() const {
	size_t counter = 0;
	for (size_t i = 0; i < _size; i++)
	{
		if (users[i]->isAdmin())
		{
			counter++;
		}
	}
	return counter;
}

User* UserCollection::operator[](size_t idx) {
	return users[idx];
}
const User* UserCollection::operator[](size_t idx) const {
	return users[idx];
}