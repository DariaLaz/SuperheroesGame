#pragma once
#include "User.h"
#include "Superhero.h"

class Player : public User
{
	double _money;
	vector<Superhero*> superheroes;
	Superhero* _main = nullptr;
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
	size_t find(const char*) const;
	Superhero* getAt(size_t);
	Superhero* main();


	void print(bool isAdmin = false) const override;
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);
	void changeMode(Superhero* superhero, const Mode& mode);

	void addSuperhero(Superhero* superhero); //-money, mode
	void loseMoney(double money);
	void winMoney(double money);

	int findSuperhero(const String& nickname);
	int findSuperhero(const char* nickname);


	void removeSuperhero(Superhero* superhero);
};

