/* game.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "game.h" // gets custom_io.h
using namespace std;
using namespace adventure_game;

Game::Game()
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

/* static */string Game::getItem(int id)
{
	/* unimplemented */
	//return item[id];			//return pointer to item
	UNREFERENCED_PARAMETER(id);
	return ""; // get it to compile
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
	player.use();
}

void Game::look()
{
	//exCout << map.current_room()->get_description();
}

void Game::move(direction d)
{
	UNREFERENCED_PARAMETER(d);
}
