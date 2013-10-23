/* item.h
 * Project: AdventureGame
 * Owner: Ethan Waddle
 * Brief: provides item functionality
 */
#ifndef ADVENTUREGAME_ITEM_H
#define ADVENTUREGAME_ITEM_H
#include <string> // get 'string' type
#include <map> // get 'map' type
#include "game_element.h"		//added this, because Compile errors

namespace adventure_game
{
	enum Items {Key, Treasure, Potion}; //This is an example of an enumeration, for disposables, if we so choose to implement disposables that way.  For example, water's effect is QUENCHED, Invisibility Potion's effect is INVISIBLE

	/* An ITEM is something that can be taken.
	 * An item is represented by two unique key identifiers: 
	 * an integer id and a string name. The user interacts with
	 * items based on the string name, whereas game elements process
	 * items based on their key integer id. The Item class has built
	 * in functionality to allow translation between these two mechanisms.
	 */
	class Item : public game_element
	{
		typedef std::string String;
	 public:
		Item();
		Item(int itemId); // create new item like the one referenced by id
		Item(String itemName); // create new item like the one referenced by name
	
		String getDescription() const {return description;}
		int getID() const {return ID;}
		bool isConsumable() const {return consumable;} 

		static bool does_item_exist(String); // does item with specified name exist
		static bool does_item_exist(int); // does item with specified id exist
		static String item_id_to_name(int); // failure returns empty string
		static int item_name_to_id(String); // failure returns -1
		// look in sub-classes to get reference to specific sub-item type (i.e. Treasure)
		static Item* get_global_item(int); // get pointer to unique item object based on id
		static Item* get_global_item(String); // get pointer to unique item object based on name
	private:
		static std::map<String,int> _itemLookupByName;
		static std::map<int,String> _itemLookupById;

		// gets 'name' from game_element (protected member)
		String description;
		int ID;
		bool consumable; //if it is consumable, we return -1 if it's already used
				 //this means that if an item is not disposable, we return true
				 //if an item is disposable and we have an unused item in our inventory, we return true

		virtual void _loadFromMarkup(const tag&);
		virtual void _writeDescription() const;
		};



	/* Disposable - any item that maintains state on whether or not it
	 * has been used; Disposables won't reimplement the markup load
	 * functionality since the status is set to true by default
	 */
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
}

#endif
