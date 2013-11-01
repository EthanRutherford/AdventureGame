/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h, gamemap.h
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace adventure_game;

namespace adventure_game{
	//not sure if this should go here, or in a different file
	//its not used yet, because it needs to be used on all comparisons on both sides.
	string tolower(string input)
	{
		char letter;
		for (unsigned int i = 0; i < input.size(); i++)
			input[i] = std::tolower(input[i]);
		return input;
	}
}

Game::Game(string name)
	: map(name.c_str())
{
	if (map.get_current_room() == NULL) // there must be at least one room
		throw GameException("The specified markup file either does not exist or is not correctly formatted.");
	map.print_story(); // if the map has a story, then print it
}

void Game::run()
{
	while (!gameover)
	{
		render();
		getInput();
		map.get_current_room()->check_lives();
		Creature* curCreature = map.get_current_room()->get_creature();
		if (curCreature->isValid())
		{
			player.takeDamage(curCreature->attack());
			player.write_health();
		}
		if (player.getHealth() <= 0)
		{
			gameover = true;
			exCout << consolea_fore_red << "You have died...\nGAME OVER";
		}
	}
}

void Game::render() const
{
	
}

void Game::getInput()
{
	if (!cin) // prevent infinite loop if end of input reached (for redirected stdin)
	{
		gameover = true;
		return;
	}
	Creature* curCreature = map.get_current_room()->get_creature();
	stringstream ss;
	string line, command;
	getline(cin, line);
	exCout.input_event(); // inform the IO manager that the user entered input
	line = tolower(line);		//uncomment once all items etc. are case insensitive
	ss.str(line); // replace (empty) contents of stringstream with line input from console
	ss >> command;
	bool safe = !(curCreature->isValid() and curCreature->isHostile());
	if (command == "look" or command == "check")
	{
		if (command == "look")
		{
			command.clear();
			ss >> command;
		}
		if (command == "at" or command == "in" or command == "check")
		{
			command.clear();
			ss >> command;
			if (curCreature->isValid() and curCreature->compare_name(command))
				curCreature->look();
			else if (!safe)
				exCout << "You have to focus!\n";
			else
			{
				Item* pitem = player.hasItem(command);
				if (pitem != NULL)
					pitem->look();	//now we can look at items in inventory
				else if (command == "health")
					player.write_health();
				else if(!map.get_current_room()->look_for(command))
					exCout << "There isn't one of those here.\n";
			}
		}
		else if (command.length() != 0)
			exCout << "Look at what?\n";
		else if (safe)
			look();
		else
			exCout << "You can't do that, you have to fight!\n"; 
	}
	else if ((command == "take" or command == "grab") and safe)
	{
		command.clear();
		ss >> command;
		if(player.stow(map.get_current_room()->take_item(command)))
			exCout << "Added to inventory.\n";
		else
			exCout << "No such item.\n";
	}
	else if (command == "open" and safe)
	{
		command.clear();
		ss >> command;
		Container* box = map.get_current_room()->search_container(command);
		Interactive* object = map.get_current_room()->search_interactive(command);
		if (box != NULL or object != NULL)
		{
			command.clear();
			ss >> command;
			if (command == "with" or command == "using")
			{
				command.clear();
				ss >> command;
				Item* pItem = player.hasItem(command);
				if (pItem == NULL)
					exCout << "You don't have one of those.\n";
				else
				{
					if (box != NULL and player.use(pItem, box))
						exCout << "It is opened.\n";
					else if (object != NULL and player.use(pItem, object))
						exCout << "";
					else
						exCout << "This item doesn't work.\n";
				}
			}
			else
				exCout << "Open with what?\n";
		}
		else 
			exCout << "No such object.\n";
	}
	else if (command == "use")
	{
		command.clear();
		ss >> command;
		if (command.length() > 0)
		{
			Item* pItem;
			//search for proper item pointer here
			pItem = player.hasItem(command);
			if (pItem == NULL)
				exCout << "You don't have one of those.\n";
			else
			{
				command.clear();
				ss >> command;
				if (command == "on" and safe)
				{
					command.clear();
					ss >> command;
					Interactive* object = map.get_current_room()->search_interactive(command);
					Container* box = map.get_current_room()->search_container(command);
					if (box != NULL)
					{
						if (player.use(pItem, box))
							exCout << "It is opened.\n";
						else
							exCout << "This item doesn't work.\n";
					}
					else if (object != NULL)
						player.use(pItem, object);
					else
						exCout << "No such object.\n";
				}
				else if (command.length() == 0)
				{
					if (!player.use(pItem))
						exCout << "You can't use that on its own.\n";
				}
				else if (!safe)
					exCout << "You're being attacked! Now's not a good time!\n";
				else
					exCout << "You can't do that.\n";
			}
		}
		else
			exCout << "Use what?\n";
	}
	else if (command == "eat")
	{
		command.clear();
		ss >> command;
		if (command.length() > 0)
		{
			Item* pItem;
			//search for proper item pointer here
			pItem = player.hasItem(command);
			if (pItem != NULL)
			{
				if (!player.use(pItem))
					exCout << "You can't use that on its own.\n";
			}
			else
				exCout << "You don't have one of those.\n";
		}
		else
			exCout << "Eat what?\n";
	}
	else if (command == "exit" || command == "quit")
		gameover = true;
	else if (command == "pack" or command == "inventory")
		player.look();
	else if ((command == "go" or command == "travel") and safe)
	{
		direction gotoDir;
		command.clear(); // in case of failure
		ss >> command;
		gotoDir = direction_from_string(command);
		if (command.length() > 0)
		{
			if (gotoDir == bad_direction)
				exCout << consolea_fore_red << "You gave an incorrect direction '" << command << "'!" << consolea_normal << "\n";
			else if ( !map.can_travel(gotoDir) ) // ensure there is a room
				exCout << consolea_fore_red << "There is no room to the " << command << "!" << consolea_normal << "\n";
			else if ( !map.travel(gotoDir) )
				exCout << consolea_fore_red << "You need to open the door to this room using " <<
					map.get_current_room()->get_door(gotoDir).get_activator() << consolea_normal << '\n';
			else //if it works
				look();
		}
		else
			exCout << consolea_fore_red << "Sytax Error: expect: go direction\n" << consolea_normal;
	}
	else if (command == "talk" and safe)
	{
		command.clear();
		ss >> command;
		if (command == "to")
		{
			command.clear();
			ss >> command;
			if (command.length() > 0)
			{
				NPC* pCharacter = map.get_current_room()->search_NPC(command);
				if (pCharacter != NULL)
					player.talk(pCharacter);
				else
					exCout << "There is no one by that name.\n";
			}
			else
				exCout << "Talk to whom?\n";
		}
		else
			exCout << "Talk to whom?\n";
	}
	else if (command == "poop")
		exCout << "ewgross\n";
	else if (command == "attack" or command == "fight")
	{
		command.clear();
		ss >> command;
		NPC* pCharacter = map.get_current_room()->search_NPC(command);
		if (pCharacter != NULL)
		{
			command.clear();
			ss >> command;
		}
		if (command == "with" or command == "using")
		{
			command.clear();
			ss >> command;
		}
		Item* pitem = player.hasItem(command);
		if (pCharacter != NULL)
		{
			if (pitem != NULL)
				pCharacter->takeDamage(player.attack(pitem));
			else
				pCharacter->takeDamage(player.attack());
			command.clear();
			ss >> command;
		}
		else
		{
			if (curCreature->isValid())
			{
				if (pitem != NULL)
					curCreature->takeDamage(player.attack(pitem));
				else
					curCreature->takeDamage(player.attack());
			}
			else
				exCout << "Nothing to attack here.\n";
		}
	}
	else if (command == "enter" and safe)
	{
		command.clear();
		ss >> command;
		if (command.length() > 0)
		{
			if (map.travel(command))
				look();
			else
				exCout << "There is no room of that name nearby.\n";
		}
		else
			exCout << "Travel where?\n";
	}
	else if (safe)
		exCout << "I don't know what that means.\nWhat would you like to do?\n";
	else
		exCout << "You can't do that now, you're being attacked!\n";
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
