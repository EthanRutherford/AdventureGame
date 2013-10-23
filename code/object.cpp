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
	unlockItem = NULL; // default not-lockable
	locked = false; // default unlocked
}
Item* Container::take(const string& itemName)
{
	if (!locked) // can only take if unlocked
	{
		// linear search for item in container
		list<Item*>::iterator iter = contents.begin(), end = contents.end();
		while (iter != end)
		{
			if ((*iter)->get_name() == itemName)
			{
				Item* tmp = *iter;
				contents.erase(iter);
				return tmp;
			}
			iter++;
		}
	}
	return NULL;
}
void Container::put(Item* item)
{
	contents.push_back(item);
}
bool Container::unlock(Item* keyItem)
{
	// if the pointers have the same address, they
	// obviously point to the same object
	if (isLockable() && unlockItem==keyItem)
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
	activatorItem = NULL;
	activated = false;
}
bool Interactive::activate(Item* item)
{
	if (item == activatorItem)
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
