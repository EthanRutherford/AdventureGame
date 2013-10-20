//Ethan Rutherford
//interface for Game, manages everything
#include "custom_io.h"

class Game{		//manages game data.. not sure what all needs to be in here yet
	public:
		void run();		//runs the game
		Game();
		~Game();
		static string strItem(int id) const;	//uses id to get item name
	private:
		Player player;
		GameMap map;						//circular list?
		Room currentRoom;					//current room
		Item* items;						//list of items from markup
		int numItems;
		Creature* creatures;				//list of creatures from markup
		int numCreatures;
		std::string help;					//contents of help
		
		void render(ostream& stream) const;	//render (needs to use Roger's stuff
		void getInput();					//read input and translate
		void take();						//friends functions maybe?
		void use();							//friends functions maybe?
		void look();						//check surroundings
		void move(/*direction*/);			//move to a room
		//other functions for game logic (if any)
};