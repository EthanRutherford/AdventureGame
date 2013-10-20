//Ethan Rutherford
//Interface for people, player and npc
#include "custom_io.h"

class Person{	//Person is pure virtual, has name and health
	public:
		std::string getName() const {return name;};
		int getHealth() const {return health;};
		virtual ~Person() = 0;
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
		void take(Room& room, int id);			//take from room
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