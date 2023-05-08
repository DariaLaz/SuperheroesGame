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
	void printMarket() const;
	

	//player funcs:
	void deleteMe(); 
	void printAll() const; //prints all players
	/*����� ����� ������ �� ���� �� ����� ������ �� ������ ������, 
		� ����� �� �������� ���� ������� ������������� �����, 
		� ����� ���� ���������� � ����� ���������� ����(��� ������� ����).*/
	void results() const; //����� ����� ������ �� ���� �� ����� ���������� ���������
	void printMarket() const;
	//��������������� ������ �� ���� �� ����� ������ ����������, ����� �� ���� ��������� � �� ���� �� ������ ���� �� ��� �� ��������, ��� �� ����� �� ������ ���.
	//����� ����� ������ �� ���� �� ����� ������ �� ���������� (����� � ��� �� ������ ������) � ��� ������� �� ������ ����� ����������. ���� ������������ ����������� ������ �� ������� �� ������. �� � ��������� ��������� �� ���� � ��� ����������, ����� ���� ����������� �� ���� ����� ���� � ���� ��������� ����� �������� ������.
	void attack(const String& nickname);
	void attack(const char* nickname); //����� ����� ������ �� ���� �� ������� ������ �� ���� ���������� �� ����� ����������.
	void changeMode(const String& nickname, const Mode& mode);
	void changeMode(const char* nickname, const Mode& mode);//����� ����� ������ �� ���� �� ������� ��������� �� ������� �� �� ��������� � ���������� � ���������.


	void login();
	void logout();
	void signUp();


	static vector<String> nicknames;
private:
	void deletePlayerAt(size_t idx);
	void deleteAdminAt(size_t idx);

	int findPlayer(const String& nickname) const;
	int findAdmin(const String& nickname) const;

	void adminCheck() const;
	void userCheck() const;
};

