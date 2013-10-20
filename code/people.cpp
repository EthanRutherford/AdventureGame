#include "people.h"
#include "game.h"

int Player::getItemCount(int id) const
{
	return invAmt[id];
}

void Player::use(int id, Interactive& object)
{
	if (invAmt[id])
	{
		exCout << "You use the " << strItem(id) << " on the "
			<< oject.getName << ", ";
		if (object.activate(id))		//activate has more output
			invAmt[id]--;
	}
	else
		exCout << "You don't have any of those.\n";
}

void Player::use(int id)
{
	//Not sure how consumables work yet
}

void take(Room& room, int id)
{
	room.take(id);
	invAmt[id]++;
}

void take(Container& thing)
{
	while (!thing.isEmpty)
		invAmt[thing.take]++;
}