/* people.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "people.h"
#include "game.h"
#include "custom_io.h"
using namespace std;
using namespace adventure_game;

void NPC::_loadFromMarkup(const tag& tagObject)
{
	UNREFERENCED_PARAMETER(tagObject);
	// needs to support the following tags
	// <name>
	// <desc>
}
void NPC::_writeDescription() const
{
}

bool Player::use(Item* pItem, Interactive* pObject)
{
	if (pObject->activate(pItem))
		if (pItem->isConsumable())
			inventory.remove(pItem);
	return true;
}
bool Player::stow(Item* pItem)
{
	if (pItem != NULL)
	{
		inventory.push_back(pItem);
		return true;
	}
	return false;
}
void Player::talk(string characterName) const
{
	NPC* pCharacter;
	// ask the current map if an NPC exists with the specified name;
	// if so, get a pointer to the NPC and have it talk or do whatever it does
	UNREFERENCED_PARAMETER(characterName);
}
void Player::_loadFromMarkup(const tag& tagObject)
{
	UNREFERENCED_PARAMETER(tagObject);
}
Item* Player::hasItem(string item_name)
{
	for (list<Item*>::iterator i = inventory.begin(), end = inventory.end(); i != end; i++)
		if ((*i)->get_name() == item_name)
			return *i;
	return NULL;
}
const Item* Player::hasItem(string item_name) const
{
	for (list<Item*>::const_iterator i = inventory.begin(), end = inventory.end(); i != end; i++)
		if ((*i)->get_name() == item_name)
			return *i;
	return NULL;
}
void Player::_writeDescription() const
{
	exCout << "Inventory:\n";
	for (list<Item*>::const_iterator i = inventory.begin(), end = inventory.end(); i != end; i++)
		exCout << (*i)->get_name() << "\n";
}
