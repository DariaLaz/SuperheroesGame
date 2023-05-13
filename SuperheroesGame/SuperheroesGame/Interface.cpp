#include "Interface.h"

void Interface::run() {
	while (true)
	{
		try
		{
			if (!_system.isLogged())
			{
				login();
				clearConsole();

				continue;
			}

			menu();
			command();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
			continue;
		}
	}
}

void Interface::menu() {
	std::cout << "+----------------+" << std::endl;
	if (_system.isAdmin())
	{
		std::cout <<"|  ADMIN MENU:   |" << std::endl
				  <<"|PRINT:          |" << std::endl
				  <<"| --Users        |" << std::endl
				  <<"| --Market       |" << std::endl
				  <<"| --Results      |" << std::endl
				  <<"| --ViewUser     |" << std::endl
				  <<"|MODIFY:         |" << std::endl
				  <<"| --AddAdmin     |" << std::endl
				  <<"| --AddPlayer    |" << std::endl
				  <<"| --DeletePlayer |" << std::endl
				  <<"| --AddToMarket  |" << std::endl
				  <<"| --Resurrect    |" << std::endl;
	}
	else
	{
		std::cout << "|  PLAYER MENU:  |" << std::endl
				  << "|PRINT:          |" << std::endl
				  << "| --Users        |" << std::endl
				  << "| --Market       |" << std::endl
				  << "| --Results      |" << std::endl
				  << "|MODIFY:         |" << std::endl
				  << "| --Buy          |" << std::endl
				  << "| --AttackUser   |" << std::endl
				  << "| --AttackHero   |" << std::endl
				  << "| --Mode         |" << std::endl;
	}
	std::cout << "|PERSONAL        |" << std::endl
			  << "| --DeleteMe     |" << std::endl
			  << "|Logout          |" << std::endl
			  << "|Exit            |" << std::endl
			  << "+----------------+" << std::endl;
}
void Interface::login() {
	std::cout << "LOGIN: \n";
	String nickname, password;
	std::cout << "Username: ";
	std::cin >> nickname;
	std::cout << "\nPassword: ";
	std::cin >> password;

	_system.login(std::move(nickname), std::move(password));


	std::cout << "You successfully logged as " << nickname << std::endl;

	while (_system.isAdmin() && _system.market().size() < 3)
	{
		std::cout << "There are less that 3 superheroes on the market. You should add superhero!\n";
		try
		{
			addSyperhero();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() <<std::endl;
		}
	}
}
void Interface::logout() {
	_system.logout();
	std::cout << "You successfully logged out " << std::endl;
}
void Interface::command() {
	String command;
	std::cout << "Enter command: ";
	std::cin >> command;
	clearConsole();

	if (command == "Users")
	{
		users();
	}
	else if (command == "Market")
	{
		market();
	}
	else if (command == "Results")
	{
		results();
	}
	else if (command == "ViewUser")
	{
		viewUser();
	}
	else if (command == "AddAdmin")
	{
		add(true);
	}
	else if (command == "AddPlayer")
	{
		add(false);
	}
	else if (command == "DeletePlayer")
	{
		deletePlayer();
	}
	else if (command == "AddToMarket")
	{
		addSyperhero();
	}
	else if (command == "Resurrect")
	{
		resurrect();
	}
	else if (command == "DeleteMe")
	{
		_system.deleteMe();
	}
	else if (command == "Logout")
	{
		logout();
	}
	else if (command == "Buy")
	{
		buy();
	}
	else if (command == "AttackUser")
	{
		attackUser();
	}
	else if (command == "AttackHero")
	{
		attackHero();
	}
	else if (command == "Mode")
	{
		changeMode();
	}
	else if (command == "Exit")
	{
		std::ofstream ofs("sys.dat", std::ios::out | std::ios::binary);
		if (!ofs.is_open())
			throw std::logic_error("Can not open the file!");
		_system.writeToBinary(ofs);
		ofs.close();
	}
	else
	{
		throw std::logic_error("Invalid command!");
	}
}
void Interface::addSyperhero() {
	String firstName, lastName, nickname, power;
	size_t strenght;
	double price;

	std::cout << "First name: ";
	std::cin >> firstName;
	std::cout << "Last name: ";
	std::cin >> lastName;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	std::cout << "Power: ";
	std::cin >> power;
	std::cout << "Strenght: ";
	std::cin >> strenght;
	std::cout << "Price: ";
	std::cin >> price;
	_system.addToMarket(firstName, lastName, nickname, getPower(power), strenght, price, Mode::notBought);
}
void Interface::resurrect() {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system.resurrect(nickname);
}
void Interface::users() const {
	std::cout << "PLAYERS: " << std::endl;
	_system.printAll();
}
void Interface::market() const {
	std::cout << "MARKET: " << std::endl;
	_system.printMarket();
}
void Interface::results() {
	std::cout << "RESULTS: " << std::endl;
	_system.results();
}
void Interface::viewUser() const {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system.printInfo(nickname);
}
void Interface::add(bool isAdmin) {
	std::cout << "ADD: " << std::endl;
	String firstName, lastName, username, password;
	std::cout << "First name: ";
	std::cin >> firstName;
	std::cout << "Last name: ";
	std::cin >> lastName;
	std::cout << "Username: ";
	std::cin >> username;
	std::cout << "Password: ";
	std::cin >> password;
	if (isAdmin)
	{
		_system.addAdmin(firstName, lastName, username, password);
		std::cout << "Admin " << username << " created successfully!" << std::endl;
	}
	else
	{
		double money;

		std::cout << "Money: ";
		std::cin >> money;

		_system.addPlayer(firstName, lastName, username, password, money);
		std::cout << "Player " << username << " created successfully!" << std::endl;
	}
}
void Interface::deletePlayer() {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system.deletePlayer(nickname);
}
void Interface::buy() {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system.buy(nickname);
}
void Interface::attackHero() {
	String myhero, opponentHero;
	std::cout << "My hero nickname: ";
	std::cin >> myhero;
	std::cout << "Opponent hero nickname: ";
	std::cin >> opponentHero;
	_system.attack(myhero, nullptr, opponentHero);
}
void Interface::attackUser() {
	String myhero, opponent;
	std::cout << "My hero nickname: ";
	std::cin >> myhero;
	std::cout << "Opponent username: ";
	std::cin >> opponent;

	_system.attack(myhero, opponent);
}
void Interface::changeMode() {
	String myhero, mode;
	std::cout << "My hero nickname: ";
	std::cin >> myhero;
	std::cout << "New mode: ";
	std::cin >> mode;

	_system.changeMode(myhero, getMode(mode));
}
void Interface::save() const {

}


//Power getPower(const String& pow) {
//	if (lower(pow) == "fire")
//	{
//		return Power::fire;
//	}
//	else if (lower(pow) == "water")
//	{
//		return Power::water;
//	}
//	else if (lower(pow) == "earth")
//	{
//		return Power::earth;
//	}
//	else
//	{
//		throw std::logic_error("Invalid power!");
//	}
//}
//Mode getMode(const String& mode) {
//	if (lower(mode) == "attack")
//	{
//		return Mode::attack;
//	}
//	else if (lower(mode) == "defence")
//	{
//		return Mode::defence;
//	}
//	else
//	{
//		throw std::logic_error("Invalid mode!");
//	}
//}
String lower(const String& str) {
	String result(str);
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			result[i] -= ('a' - 'A');
		}
	}
	return result;
}
//from Georgi Terziev's github
void clearConsole() {
	std::cout << "\033[;H";
	std::cout << "\033[J";
}

