/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h, gamemap.h
#include <sstream>
using namespace std;
using namespace adventure_game;

// Note for EthanR: I placed direction to string functions in gamemap.h, so you can call them from there...
// I made some changes just to show you how to use the stringstreams; just a demo...

Game::Game()
	: map("markup.txt") // hard code the dependency name in (we can always change it later to be passed in on the command-line)
{
}

Game::~Game()
{
}

void Game::run()
{
	while (!gameover)
	{
		render();
		getInput();
	}
}

void Game::render() const
{
	map.print_status(); // for my testing purposes (we might like this to be here, who knows?)
	exCout << "\nGive me a command!\n";
}

void Game::getInput()
{
	// let's try this instead
	// stringstreams are really powerful
	stringstream ss;
	string line, command;

	getline(cin, line);
	ss.str(line); // replace (empty) contents of stringstream with line input from console
	ss >> command;
	if (command == "look")
		;
	else if (command=="exit" || command=="quit")
		gameover = true;
	else if (command == "go")
	{
		direction gotoDir;
		command.clear(); // in case of failure
		ss >> command;
		gotoDir = direction_from_string(command);
		if (command.length() > 0)
		{
			if (gotoDir == bad_direction)
				exCout << consolea_fore_red << "You gave an incorrect direction '" << command << "'!\n";
			else if ( !map.travel(gotoDir) )
				exCout << consolea_fore_red << "There is no room to the " << command << "!\n";
			// the next render frame will display the new room status
		}
		else
			exCout << consolea_fore_red << "Sytax Error: expect: go direction\n" << consolea_normal;
			
	}


	/*
	int space[4]; //location of spaces
	int size = line.size();
	int current = 0;
	for (int i = 0; i < size; i++)
		if (line[i] == ' ')
			space[current++] = i;
	if (line.substr(0,space[0]) == "look")
		look();
	if (line.substr(0,space[0]) == "exit")
		gameover = true;
	if (line.substr(0,space[0]) == "go")
		move(direction_from_string(line.substr(space[0]+1,space[1])));*/
	/*
	
	
		here, we will determine what other function calls to make.
	
	
	*/
}

void Game::take()
{
	//player.take(map.current_room);
}

void Game::use()
{
	
}

void Game::look()
{
	map.get_current_room()->look();
}

void Game::move(direction d)
{
	if (map.can_travel(d))
		map.travel(d);
}
