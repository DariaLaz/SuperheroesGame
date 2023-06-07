#include "Admin.h"

void Admin::print(bool isAdmin) const {
	std::cout << "+++" << username() << " (admin) " << "+++\n";
}

User* Admin::clone() const {
	User* user = new Admin(*this);
	return user;
}
bool Admin::isAdmin() const {
	return true;
}
