#pragma once
#include "vector.hpp"
#include "Player.h"
#include "Admin.h"
#include "UserCollection.h"
#include "Superhero.h"

class System
{
	UserCollection users;
	vector<Superhero> market;
	User* current = nullptr;
public:
	System();

	//returns if there is logged in user
	bool isLogged() const;

	//Getters:
	//vector<Superhero> market() const;

	/*ADMIN FUNCTIONS:*/
	
	//add new aadmin
	void addUser(const User& user);
	void addUser(const char* firstName,
				  const char* lastName,
				  const char* nickname,
				  const char* password,
				  bool isAdmin);
	void addUser(const String& firstName,
				  const String& lastName,
				  const String& nickname,
				  const String& password,
				  bool isAdmin);
	void addUser(String&& firstName,
				  String&& lastName,
				  String&& nickname,
				  String&& password,
				  bool isAdmin);


	//delete player
	void deletePlayer(const String& nickname); 

	//prints info about user
	void printInfo(const String& nickname) const; 

	//add superhero to market 
	void addSuperhero(const Superhero& superhero);
	void addSuperhero(Superhero&& superhero);
	void addSuperhero(const String& firstName,
					 const String& lastName,
					 const String& _nickname,
					 const Power& power,
					 size_t strenght,
					 double price = 0.0, 
					 Mode mode = Mode::notBought); 
	void addSuperhero(String&& firstName,
					  String&& lastName,
					  String&& _nickname,
					  Power power,
					  size_t strenght,
					  double price = 0.0,
					  Mode mode = Mode::notBought); 

	//resurrect superhero
	void resurrect(const String& nickname); 
	
	//PLAYER FUNCTIONS:

	//delete current player (not if the last admin)
	void deleteMe(); 

	//print all users
	void printUsers() const;

	//print current results
	void results(); 

	//print all superheroes from market
	void printMarket() const;

	//buy superhero
	void buy(const String& nickname);
	void buy(const char* nickname);

	//attack
	int attack(const String& nickname, const String& userNickname, const String& heroNickname = nullptr);
	
	//change superhero mode
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);

	//is the current user admin
	bool isAdmin() const;

	void login(const String& nickname, const String& password);
	void logout();

	//work with files
	void writeToBinary(std::ofstream& os) const; //write in binary file
	void readFromBinary(std::ifstream& is); // read from binary file
	size_t marketSize() const;

private:
	void deleteUserAt(size_t idx);

	
	int findSuperhero(const String& nickname) const;
	int findSuperhero(const char* nickname) const;

	void adminCheck() const;
	void userCheck() const;
	void playerCheck() const;

	int comparePower(const Power& pow1, const Power& pow2) const;


	vector<Player*> players() const;

};
void writeUsersToBinary(const User* users, size_t size, std::ofstream& os);

