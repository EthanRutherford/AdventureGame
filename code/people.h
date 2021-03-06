/* people.h
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 * Brief: Interface for people, player and npc
 */
#ifndef ADVENTUREGAME_PEOPLE_H
#define ADVENTUREGAME_PEOPLE_H
#include <string> // get 'string' type
#include <list> // get 'list' type
#include "game_element.h"
#include "object.h" // get classes 'Interactive' and 'Container', gets item.h
#include "tag.h" // get 'tag' type

namespace adventure_game{
	class Person : public game_element{	//Person is abstract (because game_element is abstract), has name and health
		public:
			// gets 'get_name' from game_element
			void takeDamage(int damage);
			int getHealth() const {return health;};
		protected:
			// gets 'name' from game_element (protected member)
			int health;
			int maxHealth;
	};
	
	class NPC: public Person{		//Non players have a description, maybe some other behavior
		public:
			String talk();
			NPC() {health=10;};
		private:
			String desc;
			std::list<String> text;
			std::list<String>::iterator textIter;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};
	
	class Player: public Person{	//Players have inventory, and ability to "use"
		public:
			int getItemCount() const {return inventory.size();} // total items
			//void use(); // use an item in general, perhaps?
			bool use(Item* pItem, Interactive* object);	//attempt to use item on object
			bool use(Item* pItem, Container* box);
			bool use(Item* pItem);
			bool stow(Item* pItem);
			Item* hasItem(String name);
			const Item* hasItem(String name) const;
			int attack();
			int attack(Item* item);
			void talk(NPC* character) const;
			void write_health() const;
			Player() {health = 100; maxHealth = 100; power = 10;};
		private:
			std::list<Item*> inventory;
			int power;
			// we can load default player attributes from the markup
			// or else do nothing
			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};

}

#endif
