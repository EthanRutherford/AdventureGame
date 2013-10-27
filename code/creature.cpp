/* creature.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "creature.h"
#include "custom_io.h"
#include <stdlib.h>
#include <time.h>  
using namespace std;
using namespace adventure_game;

void Creature::_loadFromMarkup(const tag& tagObj)
{
	// supported tags for creature
	// attribute: can be name for tag
	// <name>
	// <desc>
	// <health>
	// <hostile>
	// <power>
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
		else if (tagName == "hostile")
		{
			string tmp = pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content();
			if (tmp == "true")
				hostile = true;
			else
				hostile = false;
		}
		else if (tagName == "health")
			health = atoi((pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content()).c_str());
		else if (tagName == "power")
			power = atoi((pTagIter->get_attribute().length()>0 ? pTagIter->get_attribute() : pTagIter->get_content()).c_str());
		pTagIter = tagObj.next_child();
	}
}
void Creature::_writeDescription() const
{
	exCout << desc << endl;
}
void Creature::takeDamage(int damage)
{
	if (!hostile)
		hostile = true;
	health -= damage;
}
int Creature::attack()
{
	srand (time(NULL));
	if (hostile)
	{
		int amount = power + ((rand()%5)-2); //attack with a variance of +/- 2
		exCout << consolea_fore_white << name << consolea_normal << " inflicts " << amount << " points of damage to you.\n";
		return amount;
	}
	else
		return 0;
}