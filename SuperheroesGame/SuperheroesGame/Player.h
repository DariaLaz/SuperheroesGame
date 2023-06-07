#pragma once
#include "User.h"
#include "Superhero.h"

class Player : public User
{
	double _money;
	vector<Superhero*> superheroes;
public:
	//Constructors:
	Player() = default;
	Player(const String& firstName,
		const String& lastName,
		const String& password,
		const String& nickname,
		double money = GameConstants::START_MONEY);
	Player(const char* firstName,
		const char* lastName,
		const char* password,
		const char* nickname,
		double money = GameConstants::START_MONEY);
	Player(String&& firstName,
		String&& lastName,
		String&& password,
		String&& nickname,
		double money = GameConstants::START_MONEY);

	//Getters:
	double money() const; 
	Superhero* getHeroAt(size_t idx); //returns the superhero at given index
	size_t superheroesCount() const; //Get superheroes count

	//Returns the index of the superhero (-1 if not found)
	int findHero(const char* username) const;
	int findHero(const String& username) const;

	//Print the player
	void print(bool isAdmin) const override;

	//Change mode of given superhero
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);
	void changeMode(Superhero* superhero, const Mode& mode);

	//Add new superhero to the collection
	void addSuperhero(Superhero* superhero); 

	//Decrease money
	void loseMoney(double money);
	//Increase money
	void winMoney(double money);

	//Removes the superhero from the collection
	void removeSuperhero(Superhero* superhero);

	//Work with files
	void writeToBinary(std::ofstream& os) const override; //write player in binary file
	void readFromBinary(std::ifstream& is) override; //read player from binary file

	//returns co[y of the current object
	User* clone() const override;

	bool isAdmin() const override;
};

