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
	look(); //look first
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
	//map.print_status();	//we don't actually want this here.. it conflicts with look
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
	{
		command.clear();
		ss >> command;
		if (command == "at")
		{
			command.clear();
			ss >> command;
			if(!map.get_current_room()->look_for(command))
				exCout << "There isn't one of those here.\n";
			else
				exCout << "\n";
		}
		else if (command.length() != 0)
			exCout << "Look at what?\n";
		else
			look();
	}
	else if (command == "take")
	{
		command.clear();
		ss >> command;
		if(player.stow(map.get_current_room()->take_item(command)))
			exCout << "Added to inventory.\n";
		else
			exCout << "No such item.\n";
	}
	else if (command == "open")
	{
		command.clear();
		ss >> command;
		Container* box = map.get_current_room()->search_container(command);
		if (box != NULL)
		{
			command.clear();
			ss >> command;
			if (command == "with")
			{
				command.clear();
				ss >> command;
				Item* pItem = player.hasItem(command);
				if (pItem == NULL)
					exCout << "You don't have one of those.\n";
				else
					player.use(pItem, box);
			}
			else
				exCout << "Incorrect syntax.\n";
		}
		else 
			exCout << "No such container.\n";
	}
	else if (command == "use")
	{
		command.clear();
		ss >> command;
		if (command.length() > 0)
		{
			Item* pitem;
			//search for proper item pointer here
			pitem = player.hasItem(command);
			if (pitem == NULL)
			{
				exCout << "You don't have one of those.\n";
			}
			else
			{
				command.clear();
				ss >> command;
				if (command == "on")
				{
					command.clear();
					ss >> command;
					Interactive* object = map.get_current_room()->search_interactive(command);
					if (object == NULL)
						exCout << "No such object.\n";
					else
						player.use(pitem, object);
				}
				else
					exCout << "You can't do that.\n";
			}
		}
		else
			exCout << "Use what?\n";		//try to use this type syntax for output
	}
	else if (command=="exit" || command=="quit")
		gameover = true;
	else if (command == "pack")
		player.look();
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
			else if ( !map.can_travel(gotoDir) ) // ensure there is a room
				exCout << consolea_fore_red << "There is no room to the " << command << "!\n";
			else if ( !map.travel(gotoDir) )
				exCout << consolea_fore_red << "You need to open the door to this room using " <<
					map.get_current_room()->get_door(gotoDir).get_activator() << '\n';
			else //if it works
				look();
		}
		else
			exCout << consolea_fore_red << "Sytax Error: expect: go direction\n" << consolea_normal;
	}
	else if (command == "talk")
	{
		command.clear();
		ss >> command;
		if (command.length() > 0)
		{
			command.clear();
			ss >> command;
			//call talk to person
			//if fails: exCout << "Talk to whom?";
		}
		else
			exCout << "Talk to whom?";
	}
	else if (command == "poop")
		exCout << "ewgross\n";
	else
		exCout << "I don't know what that means.\nWhat would you like to do?\n"; 
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
