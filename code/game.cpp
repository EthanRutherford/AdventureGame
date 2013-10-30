/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h, gamemap.h
#include <sstream>
#include <stdio.h>
using namespace std;
using namespace adventure_game;

// Note for EthanR: I placed direction to string functions in gamemap.h, so you can call them from there...
// I made some changes just to show you how to use the stringstreams; just a demo...

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

	// (This is not a good place to do this...)
	//ifstream markupStream(name.c_str());
	//if (markupStream) {
	//tag theTag;
        //theTag.read(markupStream);
        //if (theTag.get_name() == "story") {
	//	exCout << theTag.get_content() << endl;
	//}
	//look(); //look first
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
	Creature* curCreature = map.get_current_room()->get_creature();
	// let's try this instead
	// stringstreams are really powerful
	stringstream ss;
	string line, command;

	getline(cin, line);
	exCout.input_event(); // inform the IO manager that the user entered input
	ss.str(line); // replace (empty) contents of stringstream with line input from console
	//line = tolower(line);		//uncomment once all items etc. are case insensitive
	ss >> command;
	if (curCreature->isValid() and curCreature->isHostile())
	{
		if (command == "attack" or command == "fight")
	{
		command.clear();
		ss >> command;
		Creature* creature = map.get_current_room()->get_creature(); // why do we get the creature again on this line?
		if (command == "with" or command == "using")
		{
			command.clear();
			ss >> command;
			Item* pitem = player.hasItem(command);
			if (pitem != NULL)
				creature->takeDamage(player.attack(pitem));
		}
		else
			creature->takeDamage(player.attack());
	}
	else if (command == "look")
	{
		command.clear();
		ss >> command;
		if (command == "at")
		{
			command.clear();
			ss >> command;
			if (command == curCreature->get_name())
				curCreature->look();
			else
				exCout << "You have to focus!\n";
		}
		else
			exCout << "You can't, you're being attacked!\n";
	}
	else
		exCout << "You can't do that, you have to fight!\n"; 
	}
	else
	{
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
				Item* pitem = player.hasItem(command);
				if (pitem != NULL)
					pitem->look();	//now we can look at items in inventory
				else if (command == "health")
					player.write_health();
				else if(!map.get_current_room()->look_for(command))
					exCout << "There isn't one of those here.\n";
			}
			else if (command.length() != 0)
				exCout << "Look at what?\n";
			else
				look();
		}
		else if (command == "take" or command == "grab")
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
					else
						exCout << "You can't do that.\n";
				}
			}
			else
				exCout << "Use what?\n";
		}
		else if (command == "exit" || command == "quit")
			gameover = true;
		else if (command == "pack" or command == "inventory")
			player.look();
		else if (command == "go" or command == "travel")
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
		else if (command == "talk")
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
				Creature* creature = map.get_current_room()->get_creature(); // why do we get the creature again on this line?
				if (creature->isValid())
				{
					if (pitem != NULL)
						map.get_current_room()->get_creature()->takeDamage(player.attack(pitem));
					else
						creature->takeDamage(player.attack());
				}
				else
					exCout << "Nothing to attack here.\n";
			}
		}
		else if (command == "enter")
			exCout << "I can't do that yet."; // implement traveling via room name
		else
			exCout << "I don't know what that means.\nWhat would you like to do?\n";
	}
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
