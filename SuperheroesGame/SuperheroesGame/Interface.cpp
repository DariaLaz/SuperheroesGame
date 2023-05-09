#include "Interface.h"

void menu(System& system) {
	
	if (system.isAdmin())
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

void login(System& system) {
	std::cout << "LOGIN: \n";
	String nickname, password;
	std::cout << "Username: ";
	std::cin >> nickname;
	std::cout << "\nPassword: ";
	std::cin >> password;

	system.login(std::move(nickname), std::move(password));

	std::cout << "You successfully logged as " << nickname << std::endl;

	while (system.isAdmin() && system.market().size() < 3)
	{
		std::cout << "There are less that 3 superheroes on the market. You should add superhero!\n";
		try
		{
			addSyperhero(system);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() <<std::endl;
		}
	}
}
void logout(System& system) {
	system.logout();
	std::cout << "You successfully logged out " << std::endl;
}


void command(System& system) {
	String command;
	std::cout << "Enter command: ";
	std::cin >> command;
	if (command == "Users")
	{
		system.printAll();
	}
	else if (command == "Market")
	{
		system.printMarket();
	}
	else if (command == "Results")
	{
		system.results();
	}
	else if (command == "ViewUser")
	{
		String nickname;
		std::cout << "Nickname: ";
		std::cin >> nickname;
		system.printInfo(nickname);
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

		system.addAdmin(firstName, lastName, username, password);
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

		system.addPlayer(firstName, lastName, username, password, money);
	}
	else if (command == "DeletePlayer")
	{
		String nickname;
		std::cout << "Nickname: ";
		std::cin >> nickname;
		system.deletePlayer(nickname);
	}
	else if (command == "AddToMarket")
	{
		addSyperhero(system);
	}
	else if (command == "DeleteMe")
	{
		system.deleteMe();
	}
	else if (command == "Logout")
	{
		logout(system);
	}
	else if (command == "Buy")
	{
		String nickname;
		std::cout << "Nickname: ";
		std::cin >> nickname;
		system.buy(nickname);
	}
	else if (command == "AttackUser")
	{
		String myhero, opponent;
		std::cout << "My hero nickname: ";
		std::cin >> myhero;
		std::cout << "Opponent username: ";
		std::cin >> opponent;

		system.attack(myhero, opponent, nullptr);
	}
	else if (command == "AttackHero")
	{
		String myhero, opponentHero;
		std::cout << "My hero nickname: ";
		std::cin >> myhero;
		std::cout << "Opponent hero nickname: ";
		std::cin >> opponentHero;
		system.attack(myhero, nullptr, opponentHero);
	}
	else if (command == "Mode")
	{
		String myhero, mode;
		std::cout << "My hero nickname: ";
		std::cin >> myhero;
		std::cout << "New mode: ";
		std::cin >> mode;

		system.changeMode(myhero, getMode(mode));
	}
	else
	{
		throw std::logic_error("Invalid command!");
	}
}




Power getPower(String& pow) {
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
Mode getMode(String& mode) {
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

String& lower(String& str) {
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A'&& str[i] <= 'Z')
		{
			str[i] -= ('a' - 'A');
		}
	}
	return str;
}

void addSyperhero(System& system) {
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
	system.addToMarket(firstName, lastName, nickname, getPower(power), strenght, price, Mode::notBought);
}

//personal
void deleteMe(System& system) {
	system.deleteMe();
}
