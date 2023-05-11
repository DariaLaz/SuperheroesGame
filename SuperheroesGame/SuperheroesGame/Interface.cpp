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
			clearConsole();
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
	
	if (_system.isAdmin())
	{
		std::cout << "Admin menu: \n"
				  << "PRINT:\n"
				  << "--Users\n"
				  << "--Market\n"
				  << "--Results\n"
				  << "--ViewUser <nickname>\n"
				  << "MODIFY:\n"
				  << "--AddAdmin <firstName> <lastName> <username> <password> \n"
			      << "--AddPlayer <firstName> <lastName> <username> <password> <money>\n"
				  << "--DeletePlayer <nickname>\n"
			      << "--AddToMarket <firstName> <lastName> <nickname> <power> <strenght> <price>\n"
				  << "--Resurrect <nickname>"
			      << "PERSONAL:\n"
				  << "--DeleteMe\n"
				  << "Logout\n";
	}
	else
	{
		std::cout << "Player menu: \n"
				  << "PRINT:\n"
				  << "--Users\n"
				  << "--Market\n"
				  << "--Results\n"
				  << "--ViewUser <nickname>\n"
				  << "MODIFY:\n"
				  << "--Buy <superhero nickname>"
				  << "--AttackUser <my superhero> <oponent username>\n"
				  << "--AttackHero <my superhero> <oponent username> <oponenet superhero nickname>\n"
				  << "--Mode <superhero nickname> <new mode>"
				  << "PERSONAL:\n"
				  << "--DeleteMe\n"
				  << "Logout\n";
	}
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
	if (command == "Users")
	{
		_system.printAll();
	}
	else if (command == "Market")
	{
		_system.printMarket();
	}
	else if (command == "Results")
	{
		_system.results();
	}
	else if (command == "ViewUser")
	{
		String nickname;
		std::cout << "Nickname: ";
		std::cin >> nickname;
		_system.printInfo(nickname);
	}
	else if (command == "AddAdmin")
	{
		String firstName, lastName, username, password;
		std::cout << "First name: ";
		std::cin >> firstName;
		std::cout << "Last name: ";
		std::cin >> lastName;
		std::cout << "Username: ";
		std::cin >> username;
		std::cout << "Password: ";
		std::cin >> password;

		_system.addAdmin(firstName, lastName, username, password);
		std::cout << "Admin " << username << " created successfully!" << std::endl;

	}
	else if (command == "AddPlayer")
	{
		String firstName, lastName, username, password;
		double money;
		std::cout << "First name: ";
		std::cin >> firstName;
		std::cout << "Last name: ";
		std::cin >> lastName;
		std::cout << "Username: ";
		std::cin >> username;
		std::cout << "Password: ";
		std::cin >> password;
		std::cout << "Money: ";
		std::cin >> money;

		_system.addPlayer(firstName, lastName, username, password, money);
		std::cout << "Player " << username << " created successfully!" << std::endl;
	}
	else if (command == "DeletePlayer")
	{
		String nickname;
		std::cout << "Nickname: ";
		std::cin >> nickname;
		_system.deletePlayer(nickname);
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
		String nickname;
		std::cout << "Nickname: ";
		std::cin >> nickname;
		_system.buy(nickname);
	}
	else if (command == "AttackUser")
	{
		String myhero, opponent;
		std::cout << "My hero nickname: ";
		std::cin >> myhero;
		std::cout << "Opponent username: ";
		std::cin >> opponent;

		_system.attack(myhero, opponent, nullptr);
	}
	else if (command == "AttackHero")
	{
		String myhero, opponentHero;
		std::cout << "My hero nickname: ";
		std::cin >> myhero;
		std::cout << "Opponent hero nickname: ";
		std::cin >> opponentHero;
		_system.attack(myhero, nullptr, opponentHero);
	}
	else if (command == "Mode")
	{
		String myhero, mode;
		std::cout << "My hero nickname: ";
		std::cin >> myhero;
		std::cout << "New mode: ";
		std::cin >> mode;

		_system.changeMode(myhero, getMode(mode));
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

Power getPower(const String& pow) {
	if (lower(pow) == "fire")
	{
		return Power::fire;
	}
	else if (lower(pow) == "water")
	{
		return Power::water;
	}
	else if (lower(pow) == "earth")
	{
		return Power::earth;
	}
	else
	{
		throw std::logic_error("Invalid power!");
	}
}
Mode getMode(const String& mode) {
	if (lower(mode) == "attack")
	{
		return Mode::attack;
	}
	else if (lower(mode) == "defence")
	{
		return Mode::defence;
	}
	else
	{
		throw std::logic_error("Invalid mode!");
	}
}
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