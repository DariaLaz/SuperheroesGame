#pragma once
#include "System.h"

class Interface {
	System _system;
public:
	void run();
private:
	void menu();
	void login();
	void command();
	void addSyperhero();
	void resurrect();
	void logout();

	void users() const;
	void market() const;
	void results();
	void viewUser() const;
	void add(bool isAdmin);
	void deletePlayer();
	void buy();
	void attackHero();
	void attackUser();
	void changeMode();
	void exit() const;
};
//Power getPower(const String& pow);
//Mode getMode(const String& mode);
String lower(const String& str);

//from Georgi Terziev's github
void clearConsole();