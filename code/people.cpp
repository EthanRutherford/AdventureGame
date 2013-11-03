/* people.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "people.h"
#include "custom_io.h"
#include <stdlib.h>
#include <time.h> 
using namespace std;
using namespace adventure_game;

void Person::takeDamage(int damage)
{
	health -= damage;
}
string NPC::talk()
{
	//NPCs can have multiple lines of text, and stop at final text.
	string speech = *textIter;
	textIter++;
	if (textIter == text.end())
		textIter--;
	return speech;
}
void NPC::_loadFromMarkup(const tag& tagObj)
{
	// supported tags for NPC
	// attribute: can be name for tag
	// <name>
	// <desc>
	// <text>
	const tag* pTagIter = tagObj.next_child();
	if ( tagObj.get_attribute().length() > 0 )
		name = tagObj.get_attribute();
	while (pTagIter != NULL)
	{
		const string& tagName = pTagIter->get_name();
		if (tagName == "name")
			name = pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content();
		else if (tagName == "desc")
			desc = pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content();
		else if (tagName == "text")
		{
			string txt = pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content();
			text.push_back(txt);
		}
		pTagIter = tagObj.next_child();
	}
	textIter = text.begin();
}
void NPC::_writeDescription() const
{
	exCout << desc << endl;
}
bool Player::use(Item* pItem, Interactive* pObject)
{
	if (pObject->activate(pItem))
	{
		if (pItem->isConsumable())
			inventory.remove(pItem);
		return true;
	}
	return false;
}
bool Player::use(Item* pItem, Container* box)
{
	if (box->unlock(pItem))
	{
		if (pItem->isConsumable())
			inventory.remove(pItem);
		return true;
	}
	return false;
}
bool Player::use(Item* pItem)
{
	if (pItem->isEdible())
	{
		srand (time(NULL));
		int amount = pItem->get_power() + ((rand()%5)-2);
		health += amount;
		if (health > maxHealth)
		{
			amount -= health-maxHealth;
			health = maxHealth;
		}
		exCout << "You heal " << consolea_back_green << amount << consolea_normal << " HP.\n";
		write_health();
		if (pItem->isConsumable())
			inventory.remove(pItem);
		return true;
	}
	return false;
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
void Player::talk(NPC* character) const
{
	exCout << character->talk() << endl;;
}
int Player::attack()
{
	srand (time(NULL));
	int amount = power + ((rand()%5)-2); //attack with a variance of +/- 2
	exCout << "You inflict " << amount << " points of damage.\n";
	return amount;
}
int Player::attack(Item* item)
{
	if (!item->isEdible())
	{
		srand (time(NULL));
		int amount = power + item->get_power() + ((rand()%5)-2); //attack, adding weapon power, with a variance of +/- 2
		exCout << "You inflict " << amount << " points of damage.\n";
		return amount;
	}
	else
	return attack();
}
void Player::write_health() const
{
	if ((float)health / maxHealth < .15)
		exCout << consolea_fore_red << "Current health: " << health << "/" << maxHealth << consolea_normal << endl;
	else
		exCout << "Current health: " << health << "/" << maxHealth << endl;
}
void Player::_loadFromMarkup(const tag& tagObject)
{
	UNREFERENCED_PARAMETER(tagObject);
}
Item* Player::hasItem(string item_name)
{
	for (list<Item*>::iterator i = inventory.begin(), end = inventory.end(); i != end; i++)
		if ( (*i)->compare_name(item_name) )
			return *i;
	return NULL;
}
const Item* Player::hasItem(string item_name) const
{
	for (list<Item*>::const_iterator i = inventory.begin(), end = inventory.end(); i != end; i++)
		if ( (*i)->compare_name(item_name) )
			return *i;
	return NULL;
}
void Player::_writeDescription() const
{
	exCout << "Inventory:\n";
	for (list<Item*>::const_iterator i = inventory.begin(), end = inventory.end(); i != end; i++)
		exCout << (*i)->get_name() << "\n";
}
