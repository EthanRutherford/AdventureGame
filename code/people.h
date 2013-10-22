/* people.h
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 * Brief: Interface for people, player and npc
 */
#ifndef ADVENTUREGAME_PEOPLE_H
#define ADVENTUREGAME_PEOPLE_H
#include <string> // get 'string' type
#include <list> // get 'list' type
#include "object.h" // get classes 'Interactive' and 'Container'
#include "tag.h" // get 'tag' type

namespace adventure_game{
	class Person : public game_element{	//Person is abstract (because game_element is abstract), has name and health
		public:
			// gets 'get_name' from game_element
			int getHealth() const {return health;};
		protected:
			typedef std::string String;
			// gets 'name' from game_element (protected member)
			int health;
			int maxHealth;
	};
	
	class NPC: public Person{		//Non players have a description, maybe some other behavior
		public:
			String getDesc() const {return desc;};
			String talk() const {return text;};
		private:
			String desc;
			String text;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};
	
	class Player: public Person{	//Players have inventory, and ability to "use"
		public:
			int getItemCount() const {return inventory.size();} // total items
			int getItemCount(int id) const; // total of specific item
			//void use(); // use an item in general, perhaps?
			bool use(int itemId, Interactive& object);	//attempt to use item on object
			void stow(int id);

			void talk(String characterName) const;
		private:
			std::list<int> inventory;

			// we can load default player attributes from the markup
			// or else do nothing
			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};

}

#endif
