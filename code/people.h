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
	
	class NPC: public Person{		//Non players have a description, maybe some other behavior
		public:
			std::string getDesc() const {return desc;};
			std::string talk() const {return text;};
		private:
			std::string desc;
			std::string text;
	};
	
	class Player: public Person{	//Players have inventory, and ability to "use"
		public:
			int getItemCount(int id) const;
			void use(int id, Interactive& object);	//attempt to use item on object
			void take(room& room, int id);			//take from room
			void talk(NPC npc) const;
			Player();
			~Player();
		private:
			//Item* inventory;
			int* invAmt;
			int size;
	};

}

#endif
