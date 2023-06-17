#include "SuperHeroGame.h"
 

SuperHeroGame::SuperHeroGame() {
	_system = &(_system->getInstance());

	std::ifstream ofsGame(FileConstants::GAME_FILE_NAME, std::ios::out | std::ios::binary);
	if (!ofsGame.is_open())
		throw std::logic_error("Can not open the file!");

	ofsGame.read((char*)&turnsCounter, sizeof(size_t));
	size_t counter = currentTurnPlayers.size();
	ofsGame.read((char*)&counter, sizeof(size_t));

	for (size_t i = 0; i < counter; i++)
	{
		String currentUsername;
		currentUsername.readFromBinary(ofsGame);
		currentTurnPlayers.push_back(_system->userWith(currentUsername));
	}
	ofsGame.close();
}
void SuperHeroGame::run() {
	while (true)
	{
		try
		{
			if (!_system->isLogged())
			{
				login();
				clearConsole();

				continue;
			}

			menu();
			if (command())
				return;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			continue;
		}
	}
}

void SuperHeroGame::menu() {
	std::cout << std::endl << "+----------------+" << std::endl;
	if (_system->isAdmin())
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
			  << "|Profile         |" << std::endl
			  << "|Exit            |" << std::endl
			  << "+----------------+" << std::endl;
}
void SuperHeroGame::login() {
	std::cout << "LOGIN: \n";
	String nickname, password;
	std::cout << "Username: ";
	std::cin >> nickname;
	std::cout << "\nPassword: ";
	std::cin >> password;

	_system->login(std::move(nickname), std::move(password));


	std::cout << "You successfully logged as " << nickname << std::endl;

	if (isNewTurn())
	{
		turnsCounter++;
		currentTurnPlayers.clear();

		if (turnsCounter % GameConstants::TURN_CRITERIA == 0)
		{
			_system->giveMoney();
		}
	}
	addCurrentPlayer();


	while (_system->isAdmin() && _system->marketSize() < 3)
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
void SuperHeroGame::logout() {
	_system->logout();
	std::cout << "You successfully logged out " << std::endl;
	this->actions = 0;
}
void SuperHeroGame::increaseActions() {
	if (actions >= 3)
	{
		throw std::exception("You are out of moves.");
	}
	actions++;
}
bool SuperHeroGame::command() {
	
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
		_system->deleteMe();
	}
	else if (command == "Logout")
	{
		logout();
	}
	else if (command == "Buy")
	{
		increaseActions();
		buy();
	}
	else if (command == "AttackUser")
	{
		increaseActions();

		attackUser();
	}
	else if (command == "AttackHero")
	{
		increaseActions();

		attackHero();
	}
	else if (command == "Mode")
	{
		increaseActions();

		changeMode();
	}
	else if (command == "Profile")
	{
		profile();
	}
	else if (command == "Exit")
	{
		exit();
		return true;
	}
	else
	{
		throw std::logic_error("Invalid command!");
	}
	return false;
}
void SuperHeroGame::addSyperhero() {
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
	_system->addSuperhero(firstName, lastName, nickname, getPower(power), strenght, price, Mode::notBought);
}
void SuperHeroGame::resurrect() {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system->resurrect(nickname);
}
void SuperHeroGame::users() const {
	std::cout << "USERS: " << std::endl;
	_system->printUsers();
}
void SuperHeroGame::market() const {
	std::cout << "MARKET: " << std::endl;
	_system->printMarket();
}
void SuperHeroGame::results() {
	std::cout << "RESULTS: " << std::endl;
	_system->results();
}
void SuperHeroGame::viewUser() const {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system->printInfo(nickname);
}
void SuperHeroGame::add(bool isAdmin) {
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
	_system->addUser(firstName, lastName, username, password, isAdmin);
	std::cout << (isAdmin? "Admin " : "Player ") << username << " created successfully!" << std::endl;
}
void SuperHeroGame::deletePlayer() {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system->deletePlayer(nickname);
}
void SuperHeroGame::buy() {
	String nickname;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	_system->buy(nickname);
}
void SuperHeroGame::attackHero() {
	String myhero, opponentHero;
	std::cout << "My hero nickname: ";
	std::cin >> myhero;
	std::cout << "Opponent hero nickname: ";
	std::cin >> opponentHero;
	int money = _system->attack(myhero, nullptr, opponentHero);
	if (money >= 0)
	{
		std::cout << "You won $" << money << " againt " << opponentHero;
	}
	else
	{
		std::cout << "You lost $" << money << " againt " << opponentHero;
	}
}
void SuperHeroGame::attackUser() {
	String myhero, opponent;
	std::cout << "My hero nickname: ";
	std::cin >> myhero;
	std::cout << "Opponent username: ";
	std::cin >> opponent;

	int money = _system->attack(myhero, opponent);
	if (money >= 0)
	{
		std::cout << "You won $" << money << " againt " << opponent;
	}
	else
	{
		std::cout << "You lost $" << money << " againt " << opponent;
	}
}
void SuperHeroGame::changeMode() {
	String myhero, mode;
	std::cout << "My hero nickname: ";
	std::cin >> myhero;
	std::cout << "New mode: ";
	std::cin >> mode;

	_system->changeMode(myhero, getMode(mode));
}
void SuperHeroGame::exit() const {
	std::ofstream ofsGame(FileConstants::GAME_FILE_NAME, std::ios::out | std::ios::binary);
	if (!ofsGame.is_open())
		throw std::logic_error("Can not open the file!");

	ofsGame.write((const char*)&turnsCounter, sizeof(size_t));
	size_t counter = currentTurnPlayers.size();
	ofsGame.write((const char*)&counter, sizeof(size_t));
	for (size_t i = 0; i < counter; i++)
	{
		currentTurnPlayers[i]->username().writeToBinary(ofsGame);
	}
	ofsGame.close();


	std::ofstream ofsSys(FileConstants::SYS_FILE_NAME, std::ios::out | std::ios::binary);
	if (!ofsSys.is_open())
		throw std::logic_error("Can not open the file!");
	_system->writeToBinary(ofsSys);
	ofsSys.close();
}

bool SuperHeroGame::isNewTurn() const {
	return currentTurnPlayers.constains(_system->currentPlayer());
	
}
void SuperHeroGame::addCurrentPlayer() {
	if (!_system->currentPlayer()->isAdmin())
	{
		currentTurnPlayers.push_back(_system->currentPlayer());
	}
}

void SuperHeroGame::profile() const {
	_system->profile();
}

//from Georgi Terziev's github
void clearConsole() {
	std::cout << "\033[;H";
	std::cout << "\033[J";
}
