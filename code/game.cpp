/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h
using namespace std;
using namespace adventure_game;

namespace{	//there must be a better way than this...
direction direction_from_string(const string& s)
    {
        if (s == "north")
            return north;
        else if (s == "south")
            return south;
        else if (s == "east")
            return east;
        else if (s == "west")
            return west;
        else if (s == "northeast")
            return northeast;
        else if (s == "northwest")
            return northwest;
        else if (s == "southeast")
            return southeast;
        else if (s == "southwest")
            return southwest;
        return bad_direction;
    }
}
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
	exCout << "Give me a command!\n";
}

void Game::getInput()
{
	std::string line;
	getline(cin, line);
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
		move(direction_from_string(line.substr(space[0]+1,space[1])));
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
