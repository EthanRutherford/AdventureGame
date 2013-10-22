/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h
using namespace std;
using namespace adventure_game;

Game::Game()
	: map("markup.txt")
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

/* static */Item* Game::getItem(int id)
{
	/* unimplemented */
	//return item[id];			//return pointer to item
	UNREFERENCED_PARAMETER(id);
	return NULL; // get it to compile
}

void Game::render() const
{
	//?
}

void Game::getInput()
{
	std::string line;
	getline(cin, line);
	
}

void Game::take()
{
	//player.take(map.current_room);
}

void Game::use()
{
	//player.use(); // no such member function
}

void Game::look()
{
	//exCout << map.current_room()->get_description();
}

void Game::move(direction d)
{
	UNREFERENCED_PARAMETER(d);
}
