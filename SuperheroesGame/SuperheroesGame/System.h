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
	User current;
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
				   double money);//Всеки администратор трябва да може да добавя нови администратори и играчи в системата.
	void deletePlayer(const String& nickname);
	void deletePlayer(const char* nickname); //Всеки администратор трябва да може да изтрива профили на играчи.
	void printInfo(const String& nickname) const;
	void printInfo(const char* nickname) const;
	//Всеки администратор трябва да има права да вижда цялата информацията за всеки потребител и неговия прогрес(без администраторите, един администратор може да вижда само имената и имейла на друг администратор) .
	void addToMarket(const Superhero& superhero);
	void addToMarket(const String& firstName,
					 const String& lastName,
					 const Power& power,
					 size_t strenght,
					 double price = 0.0, 
					 Mode mode = Mode::notBought);
	//Всеки администратор трябва да може да добавя нови супергерои към “пазара”. В случай, че на “пазара” няма никакви супергерои, администраторът още с влизането си трябва да добави поне 3 супергероя. Администраторът трябва да може да вижда всички супергерои, които са били продадени и да може да избере един от тях за добавяне, ако не желае да добавя нов.
	vector<Superhero> market() const;
	

	//player funcs:
	void deleteMe(); //Всеки играч трябва да може да изтрива профила си.
	void printAll() const; //prints all players
	/*Всеки играч трябва да може да вижда списък от всички играчи, 
		в който са записани само техните потребителски имена, 
		с колко пари разполагат и какви супергерои имат(без тяхната сила).*/
	void results() const; //Всеки играч трябва да може да вижда моментното класиране
	void printMarket() const;
	//Администраторът трябва да може да вижда всички супергерои, които са били продадени и да може да избере един от тях за добавяне, ако не желае да добавя нов.
	//Всеки играч трябва да може да вижда пазара от супергерои (който е общ за всички играчи) и при желание да закупи някой супергерой. След закупуването супергероят трябва да изчезне от пазара. Не е позволено дублиране на един и същ супергерой, както като собственост на един играч така и като дублиране между различни играчи.
	void attack(const String& nickname);
	void attack(const char* nickname); //Всеки играч трябва да може да нападне избран от него супергерой на даден потребител.
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);//Всеки играч трябва да може да променя позицията на героите си от атакуваща в дефанзивна и обратното.

	void logout();


	static vector<String> nicknames;
};

