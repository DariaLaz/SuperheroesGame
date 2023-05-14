#pragma once
#include "vector.hpp"
#include "Player.h"
#include "Superhero.h"


class System
{
	vector<User> _admins;
	vector<Player> _players;
	vector<Superhero> _market;
	bool _isAdmin;
	User* current = nullptr;
public:
	System();

	//returns if there is logged in user
	bool isLogged() const;

	//Getters:
	vector<Superhero> market() const;

	//ADMIN FUNCTIONS::
	void addAdmin(const User& user); //add new admin
	void addAdmin(User&& user); //add new admin
	void addAdmin(const char* firstName,
				  const char* lastName,
				  const char* nickname,
				  const char* password); //add new admin
	void addAdmin(const String& firstName,
				  const String& lastName,
				  const String& nickname,
				  const String& password); //add new admin
	void addAdmin(String&& firstName,
				  String&& lastName,
				  String&& nickname,
				  String&& password); //add new admin
	void addPlayer(const Player& player);//add new player
	void addPlayer(Player&& player);//add new player
	void addPlayer(const char* firstName,
				   const char* lastName,
				   const char* nickname,
				   const char* password,
				   double money);//add new player
	void addPlayer(const String& firstName,
				   const String& lastName,
				   const String& nickname,
				   const String& password,
				   double money);//add new player
	void addPlayer(String&& firstName,
				   String&& lastName,
				   String&& nickname,
				   String&& password,
				   double money);//add new player
	void deletePlayer(const String& nickname); //delete player
	void printInfo(const String& nickname) const; //prints info about user
	void addSuperhero(const Superhero& superhero); //add superhero to market 
	void addSuperhero(Superhero&& superhero);//add superhero to market 
	void addSuperhero(const String& firstName,
					 const String& lastName,
					 const String& _nickname,
					 const Power& power,
					 size_t strenght,
					 double price = 0.0, 
					 Mode mode = Mode::notBought); //add superhero to market 
	void addSuperhero(String&& firstName,
					  String&& lastName,
					  String&& _nickname,
					  Power power,
					  size_t strenght,
					  double price = 0.0,
					  Mode mode = Mode::notBought); //add superhero to market 
	void resurrect(const String& nickname); //resurrect superhero
	
	//PLAYER FUNCTIONS:
	void deleteMe(); 
	void printPlayers() const;
	void printAdmins() const;
	void results(); 
	void printMarket() const;
	void buy(const String& nickname);
	void buy(const char* nickname);
	int attack(const String& nickname, const String& userNickname, const String& heroNickname = nullptr);
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);

	bool isAdmin() const;


	void login(const String& nickname, const String& password);
	void logout();

	//work with files
	void writeToBinary(std::ofstream& os) const; //write in binary file
	void readFromBinary(std::ifstream& is); // read from binary file
private:
	void deletePlayerAt(size_t idx);
	void deleteAdminAt(size_t idx);

	int findPlayer(const String& nickname) const;
	int findAdmin(const String& nickname) const;
	int findSuperhero(const String& nickname) const;
	int findSuperhero(const char* nickname) const;

	void adminCheck() const;
	void userCheck() const;
	void playerCheck() const;

	int comparePower(const Power& pow1, const Power& pow2) const;

	void sort();
};
void writeUsersToBinary(const User* users, size_t size, std::ofstream& os);

