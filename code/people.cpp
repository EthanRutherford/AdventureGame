/* people.cpp
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 */
#include "people.h"
#include "game.h"
#include "custom_io.h"
using namespace std;
using namespace adventure_game;

Player::Player()
{
}
Player::~Player()
{
}
int Player::getItemCount(int id) const
{
	return invAmt[id];
}

void Player::use(int id, Interactive& object)
{
	if (invAmt[id])
	{
		exCout << "You used the " << consolea_fore_blue << Game::strItem(id) << consolea_normal << " on the "
			<< object.getName() << ", ";
		if (object.activate(id))		//activate has more output
			invAmt[id]--;
	}
	else
		exCout << "You don't have any of those.\n";
}

void Player::use(int id)
{
	UNREFERENCED_PARAMETER(id); // prevent compiler warning
	//Not sure how consumables work yet
}

void Player::take(room& r, int id)
{
	UNREFERENCED_PARAMETER(r); // prevent compiler warning
	//r.take(id); // until such time as the room class supports this...
	invAmt[id]++;
}

void Player::take(Container& thing)
{
	while (!thing.isEmpty())
		invAmt[thing.take()]++;
}
