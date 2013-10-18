//Ethan Rutherford
//Interface for people, player and npc

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
		Item getItem(int id) const;
		int getItemCount(int id) const;
		void use(int id, Interactive object);	//attempt to use item on object
		void use(int id);						//use consumable item
	private:
		Item inventory[25];		//placeholder number
		int invAmt[25];
};

class NPC: public Person{		//Non players have a description, maybe some other behavior
	public:
		std::string getDesc() const {return desc;};
	private:
		std::string desc;
};