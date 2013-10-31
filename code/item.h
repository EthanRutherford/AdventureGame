/* item.h
 * Project: AdventureGame
 * Owner: Ethan Waddle
 * Brief: provides item functionality
 */
#ifndef ADVENTUREGAME_ITEM_H
#define ADVENTUREGAME_ITEM_H
#include <string> // get 'string' type
#include <map> // get 'map' type
#include "game_element.h" // get 'game_element' base, gets tag.h

namespace adventure_game
{
	// An ITEM is something that can be taken.
	class Item : public game_element
	{
		public:
			// gets 'get_name' from game_element
			String getDescription() const {return description;}
			bool isConsumable() const {return consumable;} 
			int get_power() {return power;}

			// use these functions to create items; since we use
			// items with reference semantics only			
			static Item* create_item(const tag& fromTag); // create new item from markup
			static Item* create_item(Item* pFromItem); // create new item based on existing item
		private:
			// don't allow users to create an item; they must use item create functions
			// implement reference semantics for items
			Item();
			Item(int itemId); // create new item like the one referenced by id
			Item(const Item&);
			Item& operator =(const Item&); // left unimplemented
			int power;

			// gets 'name' from game_element (protected member)
			String description;
			bool consumable; //if it is consumable, we return -1 if it's already used
					 //this means that if an item is not disposable, we return true
					 //if an item is disposable and we have an unused item in our inventory, we return true

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};
}

#endif
