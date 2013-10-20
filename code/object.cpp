#include "object.h"
#include "game.h"

//Container functions

std::string Container::peek() const	//returns string list of contents
{
	std::string ans = "";
	for (int i = 0; i < size; i++)
		ans += strItem(i) + ((i != size-1)? ", ": "");
	return ans;
}

int Container::take()		//sends items to player::take; Nulls contents
{
	int ans = contents[--size];
	if (size = 0)
		contents = NULL;
	return ans;
}

Container::Container()
{
	//Roger's markup stuff
}

Container::~Container()
{
	if (contents != NULL)
		delete [] contents;
}

//Interactive functions

bool activate(int id)
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

Interactive()
{
	//Roger's Markup stuff
}