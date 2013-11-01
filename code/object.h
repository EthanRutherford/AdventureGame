/* object.h
 * Owner: Ethan Rutherford
 * Brief: Interface for objects; objects are found in rooms
 */
#ifndef ADVENTUREGAME_OBJECT_H
#define ADVENTUREGAME_OBJECT_H
#include <string> // just need std::string for header
#include <list>
#include "game_element.h"
#include "item.h"

namespace adventure_game{
	class Object : public game_element {		//Objects are physical things that exist in (belong to) rooms
		public:
			const String& getDescription() const {return desc;}
		protected:

			// gets game_element::name (protected member)
			String desc; // every object needs a description
	};

	class Aesthetic: public Object{		//as name suggests, merely aesthetic
		private:
			// gets game_element::name
			// gets Object::desc

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};

	class Container: public Object{		//an object that has item(s) in it
		public:
			Container();

			Item* take(const String& itemName); // take first occurance of item with matching name; return NULL if not found
			void put(Item* itemId); // stow item in container

			// gets the Item referred to by the specified name
			// or returns NULL if none was found
			const Item* search_item(const String& objName) const;
			Item* search_item(const String& objName);

			int getCount() const {return contents.size();}
			bool isEmpty() const {return contents.size()==0;}			//is it empty?
			bool isLocked() const {return locked;}
			bool isLockable() const {return unlockItemName.length()>0;}
			bool unlock(const Item* pUnlockItem); // attempt to open the container with the specified item

			void setName(const String& newName) {name = newName;}
		private:
			std::list<Item*> contents; // items inside the container
			String unlockItemName;
			bool locked;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const; //see what's inside
	};

	class Interactive: public Object{	//an object that an item can be used on
		public:
			Interactive();

			bool isActive() const {return activated;}
			bool activate(const Item* id); //if correct item id, change activated state, return true if correct item
			bool has_activator() const {return activatorItemName.length()>0;}
			const String& get_activator() const {return activatorItemName;} // use this when checking player inventory
			String getRoomName() {return linkedRoomName;}
		private:
			String linkedRoomName;
			String activatorItemName;
			bool activated;
			String successMessage;
			String failureMessage;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};
}

#endif
