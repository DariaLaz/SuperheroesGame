#pragma once
#include "User.h"
class Player : public User
{
	double _money;
public:
	Player() = default;
	Player(const String& firstName,
		const String& lastName,
		const String& password,
		const String& nickname,
		double money);
	Player(const char* firstName,
		const char* lastName,
		const char* password,
		const char* nickname,
		double money);
	double money() const;

	void print(bool isAdmin = false) const override;
};

