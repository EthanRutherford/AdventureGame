/* object.h
 * Owner: Ethan Rutherford
 * Brief: Interface for objects
 */
#ifndef ADVENTUREGAME_OBJECT_H
#define ADVENTUREGAME_OBJECT_H
#include <string> // just need std::string for header
#include <list>
#include "game_element.h"

namespace adventure_game{
	class Object : public game_element {		//Objects are physical things that exist in (belong to) rooms
		protected:
			typedef std::string String;

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

			bool take(int itemId);
			void put(int itemId);

			int getCount() const {return contents.size();}
			bool isEmpty() const {return contents.size()==0;}			//is it empty?
			bool isLocked() const {return locked;}
			bool isLockable() const {return unlockId!=-1;}
			bool unlock(int itemId);
		private:
			std::list<int> contents; // ids of items that are inside the container
			int unlockId;
			bool locked;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const; //see what's inside
	};

	class Interactive: public Object{	//an object that an item can be used on
		public:
			Interactive();

			bool isActive() const {return activated;}
			bool activate(int id); //if correct item id, change activated state, return true if correct item
		private:
			int activatorId;
			bool activated;
			String successMessage;
			String failureMessage;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};
}

#endif
