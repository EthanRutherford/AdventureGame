/* people.h
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 * Brief: Interface for people, player and npc
 */
#ifndef ADVENTUREGAME_PEOPLE_H
#define ADVENTUREGAME_PEOPLE_H
#include <string> // just need std::string for header
#include "object.h" // get classes 'Interactive' and 'Container'
#include "gamemap.h" // get class 'room'

namespace adventure_game{
	class Person{	//Person is pure virtual, has name and health
		public:
			std::string getName() const {return name;};
			int getHealth() const {return health;};
			virtual ~Person() {};
		protected:
			std::string name;
			int health;
			int maxHealth;
	};

	class Player: public Person{	//Players have inventory, and ability to "use"
		public:
			int getItemCount(int id) const;
			void use(int id, Interactive& object);	//attempt to use item on object
			void use(int id);						//use consumable item
			void take(room& room, int id);			//take from room
			void take(Container& thing);			//take from container
			Player();
			~Player();
		private:
			//Item* inventory;
			int* invAmt;
			int size;
	};

	class NPC: public Person{		//Non players have a description, maybe some other behavior
		public:
			std::string getDesc() const {return desc;};
		private:
			std::string desc;
	};
}

#endif
