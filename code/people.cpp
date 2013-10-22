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

int Player::getItemCount(int id) const
{
	int cnt = 0;
	for (list<int>::const_iterator iter = inventory.begin(), end = inventory.end();iter!=end;iter++)
		if (*iter == id)
			cnt++;
	return cnt;
}
bool Player::use(int itemId, Interactive& object)
{
	UNREFERENCED_PARAMETER(itemId);
	UNREFERENCED_PARAMETER(object);
	return false; // unimplemented
}
void Player::stow(int itemId)
{
	inventory.push_back(itemId);
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
void Player::_writeDescription() const
{
	// may just leave this blank
	// but is called when using the 
	// look() member function from game_element
}
