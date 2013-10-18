//Ethan Rutherford
//Interface for objects

class Object{		//Objects are physical things that exist in (belong to) rooms
	public:
		std::string getName() const {return name;};
		std::string getDesc() const {return desc;};
		virtual ~Object() = 0;
	protected:
		std::string name;
		std::string desc;
};

class Aesthetic: public Object{		//as name suggests, merely aesthetic
	public:
		Aesthetic(std::string Name, std::string Desc): name(Name), desc(Desc);
};

class Container: public Object{		//an object that has item(s) in it
	public:
		std::string peek() const;	//see what's inside
		Item take();				//take what's inside (and remove from contents)
		Container();				//figure out initialization later.
		~Container();
	private:
		Item* contents();
};

class Interactive: public Object{	//an object that an item can be used on
	public:
		bool isActive() const {return activated;};
		bool activate(int id); //if correct item id, change activated state, return true if correct item
		Interactive();
	private:
		int activatorId;
		bool activated;
		std::string successMessage;
		std::string failureMessage;
};