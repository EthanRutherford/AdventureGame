/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h, gamemap.h
using namespace std;
using namespace adventure_game;

// Note for EthanR: I placed direction to string functions in gamemap.h, so you can call them from there...

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
