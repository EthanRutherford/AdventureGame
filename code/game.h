//Ethan Rutherford
//interface for Game, manages everything

class Game{		//manages game data.. not sure what all needs to be in here yet
	public:
		void run();		//runs the game
	private:
		Player player;
		Room* room;
};