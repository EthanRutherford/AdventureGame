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
	enum Items {KEY, TREASURE, POTION}; //This is an example of an enumeration, for disposables, if we so choose to implement disposables that way.  For example, water's effect is QUENCHED, Invisibility Potion's effect is INVISIBLE

	/* An ITEM is something that can be taken.
	 *  An Item is a special class implemented with reference semantics. You create
	 *  an Item by using the "create_item" functions declared in this header. The markup
	 *  loading functions ideally should be the only code that uses them, unless another kind
	 *  of object needs to create new items during the game. Once created, an Item exists in memory until the main
	 *  function quits. You NEVER have to call delete on an Item*. An Item* functions as the item's 
	 *  id value (each pointer is unique), and other game elements that use Items maintain a list of
	 *  Item pointers. When an item needs to move between elements, the pointer should be copied, then
	 *  removed from the original element. When one wants to lookup an item, all they have to do is
	 *  deference the pointer.
	 *  Searching for an item: the game element types refer to Items via Item*. The user refers to items via
	 *  a string item-name. Different items could have the same item-name. For example, a container in one room 
	 *  can have a Potion and so could a container in another room. Therefore, when searching (taking, ETC.) an
	 *  item, a game element (the one that you are searching through or taking from) accepts an item name string
	 *  and gets the first item in its list that matches the name. For example:
	 *
	 *	Player in Room1
	 *		There's a chest in Room1, player looks inside; items are: Potion, Potion, Paper, Loaf of Bread
	 *		Player asks to take item "Potion"; chest returns Item* to first Potion in the chest
	 *		Remaining items in chest: Potion, Paper, Loaf of Bread
	 * This way, since the request for name to Item* lookup is performed by the operating game element object,
	 * the logical item requested can be retrieved. In the above example, each Potion is a separate instantiation of class
	 * Item (via Disposable). Both have the same user-ID (name), but that can be narrowed down in the context of a specific
	 * game element.
	 */
	class Item : public game_element
	{
		friend Item* create_item(const tag&);
		friend Item* create_item(Item*);
		typedef std::string String;
	 public:
		// gets 'get_name' from game_element
		String getDescription() const {return description;}
		bool isConsumable() const {return consumable;} 
	private:
		// don't allow users to create an item; they must use item create functions
		// implement reference semantics for items
		Item();
		Item(int itemId); // create new item like the one referenced by id
		Item(const Item&);
		Item& operator =(const Item&); // left unimplemented

		// gets 'name' from game_element (protected member)
		String description;
		bool consumable; //if it is consumable, we return -1 if it's already used
				 //this means that if an item is not disposable, we return true
				 //if an item is disposable and we have an unused item in our inventory, we return true

		virtual void _loadFromMarkup(const tag&);
		virtual void _writeDescription() const;
		};

	// use these functions to create items; since we use
	// items with reference semantics only
	Item* create_item(const tag&); // create new item from markup
	Item* create_item(Item* pItem); // create new item based on existing item

	
	/* Disposable - any item that maintains state on whether or not it
	 * has been used; Disposables won't reimplement the markup load
	 * functionality since the status is set to true by default
	 */
/*
	class Disposable: public Item //potions, etc.
	{
	 public:
		Disposable();
	
		bool getStatus()const{return Status;}
		void setStatus(bool newStatus){Status=newStatus;}
	
	 private:
		bool Status; //can be initialized to true, meaning can be used.  For example, a potion in inventory that has not been drunk will be true.
	
		virtual void _writeDescription() const;
	 };

	class Treasure: public Item //a Treasure Item has a value
	{
	 public:
		Treasure();

		double getValue()const{return Value;}
	 	void setValue(double newValue){Value=newValue;}
	 private:
		double Value;

		virtual void _loadFromMarkup(const tag&);
		virtual void _writeDescription() const;
	 };
*/
}

#endif
