#pragma once
#include "System.h"

class SuperHeroGame {
	System* _system = nullptr;

	vector<const User*> currentTurnPlayers;
	size_t turnsCounter = 0;
public:
	SuperHeroGame();
	void run();

private:
	//Turns manager
	bool isNewTurn() const;
	void addCurrentPlayer();

	void profile() const;

	//Print menu
	void menu();
	//Login
	void login();
	//Get new command
	bool command();
	//Add superhero to market
	void addSyperhero();
	//Resurrect dead superhero
	void resurrect();
	//Logout
	void logout();
	//Print all users
	void users() const;
	//Print all superheroes
	void market() const;
	//Print current results
	void results();
	//Print someone's data
	void viewUser() const;
	//Add user
	void add(bool isAdmin);
	//delete user
	void deletePlayer();
	//Buy superhero
	void buy();

	void attackHero();
	void attackUser();

	void changeMode();

	void exit() const;
};

//from Georgi Terziev's github
void clearConsole();