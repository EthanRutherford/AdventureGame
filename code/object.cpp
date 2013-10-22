#include "object.h"
#include "game.h"
#include "custom_io.h"
using namespace std;
using namespace adventure_game;

//Container functions

string Container::peek() const	//returns string list of contents
{
	String ans = "";
	for (int i = 0; i < size; i++)
		ans += Game::getItem(i)->getName() + ((i != size-1)? ", ": "");
	return ans;
}

int Container::take()		//sends items to player::take; Nulls contents
{
	int ans = contents[--size];
	if (size == 0)
		contents = NULL;
	return ans;
}

Container::Container()
{
	//Roger's markup stuff -- will derive into Object a type that handles this
	// and then override a virtual function in this class
	contents = NULL;
}

Container::~Container()
{
	if (contents != NULL)
		delete [] contents;
}

//Interactive functions

bool Interactive::activate(int id)
{
	if (id == activatorId)
	{
		activated = true;
		exCout << successMessage;
	}
	else
		exCout << failureMessage;
	return activated;
}

Interactive::Interactive()
{
	
}
