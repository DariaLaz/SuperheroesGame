#pragma once
#include "vector.hpp"
#include "Player.h"
#include "Superhero.h"


class System
{
	vector<User> _admins;
	vector<Player> _players;
	vector<Superhero> _market;
	bool isAdmin;
	User* current = nullptr;
public:
	System();

	//admin funcs:
	void addAdmin(const User& user);
	void addAdmin(User&& user);
	void addAdmin(const char* firstName,
				  const char* lastName,
				  const char* nickname,
				  const char* password);
	void addAdmin(const String& firstName,
				  const String& lastName,
				  const String& nickname,
				  const String& password);
	void addPlayer(const Player& player);
	void addPlayer(Player&& player);
	void addPlayer(const char* firstName,
				   const char* lastName,
				   const char* nickname,
				   const char* password,
				   double money);
	void addPlayer(const String& firstName,
				   const String& lastName,
				   const String& nickname,
				   const String& password,
				   double money);
	void deletePlayer(const String& nickname); 
	void printInfo(const String& nickname) const;
	void addToMarket(const Superhero& superhero);
	void addToMarket(Superhero&& superhero);
	void addToMarket(const String& firstName,
					 const String& lastName,
					 const String& _nickname,
					 const Power& power,
					 size_t strenght,
					 double price = 0.0, 
					 Mode mode = Mode::notBought);
	vector<Superhero> market() const;
	

	//player funcs:
	void deleteMe(); 
	void printAll() const; 
	void results() const; 
	void printMarket() const;
	void buy(const String& nickname);
	void buy(const char* nickname);
	int attack(const String& nickname, const String& userNickname, const String& heroNickname);
	int attack(const char* attackerNickname, const char* userNickname, const char* heroNickname);
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);


	void login();
	void logout();
	void signUp();


	static vector<String> nicknames;
private:
	void deletePlayerAt(size_t idx);
	void deleteAdminAt(size_t idx);

	int findPlayer(const String& nickname) const;
	int findAdmin(const String& nickname) const;
	int findSuperhero(const String& nickname) const;
	int findSuperhero(const char* nickname) const;

	int comparePower(const Power& pow1, const Power& pow2) const; // 0 ==, -1 <, 1 >

	void adminCheck() const;
	void userCheck() const;
	void playerCheck() const;
};

