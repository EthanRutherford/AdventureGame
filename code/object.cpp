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
	exCout << desc;
}

//Container functions
Container::Container()
{
	// default unlockable
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
const Item* Container::search_item(const string& objName) const
{
	for (list<Item*>::const_iterator iter = contents.begin(), end = contents.end();iter!=end;iter++)
		if ((*iter)->get_name() == objName)
			return *iter;
	return NULL;
}
Item* Container::search_item(const string& objName)
{
	for (list<Item*>::iterator iter = contents.begin(), end = contents.end();iter!=end;iter++)
		if ((*iter)->get_name() == objName)
			return *iter;
	return NULL;
}
bool Container::unlock(const Item* keyItem)
{
	// if the pointers have the same address, they
	// obviously point to the same object
	if (isLockable() && keyItem!=NULL && unlockItemName==keyItem->get_name())
	{
		locked = false;
		return true;
	}
	return false;
}
void Container::_loadFromMarkup(const tag& tagObj)
{
	// supported tags for Container
	// attribute: can be name for tag
	// <name>
	// <item>
	// <lock itemName/>  OR <lock>itemName</lock>
	const tag* pTagIter = tagObj.next_child();
	if ( tagObj.get_attribute().length() > 0 )
		name = tagObj.get_attribute();
	while (pTagIter != NULL)
	{
		const string& tagName = pTagIter->get_name();
		if (tagName == "name")
			name = pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content();
		else if (tagName == "item")
			contents.push_back( create_item(*pTagIter) );
		else if (tagName == "lock")
		{
			unlockItemName = pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content();
			locked = true;
		}
		pTagIter = tagObj.next_child();
	}
}
void Container::_writeDescription() const
{
	if (!locked && contents.size()>0)
	{
		//output the contents
		exCout << "Contents of " << consolea_fore_blue << name << consolea_normal << ":";
		for (list<Item*>::const_iterator iter = contents.begin(), end = contents.end();iter!=end;iter++)
			exCout << "\n\t" << (*iter)->get_name();
	}
	else if (isLockable())
		exCout << "It won't open. You need to find the " << consolea_fore_green << unlockItemName << consolea_normal << '.';
}

//Interactive functions
Interactive::Interactive()
{
	// default has no activator
	activated = false;
}
bool Interactive::activate(const Item* item)
{
	if (item->get_name() == activatorItemName)
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
	// <object> OR <door> - content string is activator item name
	// supported sub-tags
	//  <desc>
	//  <name>
	//  <activator>
	//  <success-msg>
	//  <fail-msg>
	const tag* pIter = tagObj.next_child();
	while (pIter != NULL)
	{
		const string& tagName = pIter->get_name();
		if (tagName == "desc")
			desc = pIter->get_attribute().length()>0 ? pIter->get_attribute() : pIter->get_content();
		else if (tagName == "name")
			name = pIter->get_attribute().length()>0 ? pIter->get_attribute() : pIter->get_content();
		else if (tagName == "activator")
			activatorItemName = pIter->get_attribute().length()>0 ? pIter->get_attribute() : pIter->get_content();
		else if (tagName == "success-msg")
			successMessage = pIter->get_attribute().length()>0 ? pIter->get_attribute() : pIter->get_content();
		else if (tagName == "fail-msg")
			failureMessage = pIter->get_attribute().length()>0 ? pIter->get_attribute() : pIter->get_content();
		pIter = tagObj.next_child();
	}

}
void Interactive::_writeDescription() const
{
	exCout << desc;
}
