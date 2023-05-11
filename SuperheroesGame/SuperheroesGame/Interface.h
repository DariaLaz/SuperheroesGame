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
};
Power getPower(const String& pow);
Mode getMode(const String& mode);
String lower(const String& str);

//from Georgi Terziev's github
void clearConsole();