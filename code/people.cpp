#include "people.h"

Item Player::getItem(int id) const
{
	return inventory[id];
}

int Player::getItemCount(int id) const
{
	return invAmt[id];
}

void Player::use(int id, Interactive& object)
{			//may need to rewrite this to use roger's output methods
	if (invAmt[id])
	{									//unless different method
		std::cout << "You use the " << Inventory[id].getName() << " on the "
			<< oject.getName << ", ";
		if (object.activate(id))		//activate has more output
		{
			invAmt[id]--;
		}
	}
	else
		std::cout << "You don't have any of those.\n";
}

void Player::use(int id)
{
	//Not sure how consumables work yet
}