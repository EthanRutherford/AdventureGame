#include "object.h"
#include "game.h"
#include "custom_io.h"
using namespace std;
using namespace adventure_game;

void Aesthetic::_loadFromMarkup(const tag& tagObj)
{
	UNREFERENCED_PARAMETER(tagObj);
}
void Aesthetic::_writeDescription() const
{
}

//Container functions
Container::Container()
{
	unlockId = -1; // default not-lockable
	locked = false; // default unlocked
}
bool Container::take(int itemId)
{
	if (!locked) // can only take if unlocked
	{
		list<int>::iterator iter = contents.begin(), end = contents.end();
		while (iter != end)
		{
			if (*iter == itemId)
			{
				contents.erase(iter);
				return true;
			}
			iter++;
		}
	}
	return false;
}
void Container::put(int itemId)
{
	contents.push_back(itemId);
}
bool Container::unlock(int ID)
{
	if (isLockable() && ID==unlockId)
	{
		locked = false;
		return true;
	}
	return false;
}
void Container::_loadFromMarkup(const tag& tagObj)
{
	UNREFERENCED_PARAMETER(tagObj);
}
void Container::_writeDescription() const
{
	if (!locked)
	{
		
		exCout << "Hey! I unlocked this or something...?";
	}
	exCout << "I haven't opened it yet.";
}

//Interactive functions
Interactive::Interactive()
{
	activatorId = -1;
	activated = false;
}
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
void Interactive::_loadFromMarkup(const tag& tagObj)
{
	UNREFERENCED_PARAMETER(tagObj);
}
void Interactive::_writeDescription() const
{
}
