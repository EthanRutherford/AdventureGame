/* game.h
 * Owner: Ethan Rutherford
 * Brief: interface for Game, manages everything
 */
#ifndef ADVENTUREGAME_GAME_H
#define ADVENTUREGAME_GAME_H
#include "custom_io.h" // get iostream types and 'direction' enum type
#include "gamemap.h" // get class 'gamemap'
#include "people.h" // get class 'Player'

namespace adventure_game{
	class Game{		//manages game data.. not sure what all needs to be in here yet
		public:
			void run();		//runs the game
			Game();
			~Game();
			static std::string strItem(int id);	//uses id to get item name
		private:
			Player player;
			gamemap map;						//managed the rooms of the game world
			//Item* items;						//list of items from markup
			int numItems;
			//Creature* creatures;				//list of creatures from markup
			int numCreatures;
			std::string help;					//contents of help
		
			// let's just always use the 'exCout' stream object declared in custom_io.h
			// which is #included into this class's implementation file
			//void render(ostream& stream) const;	//render (needs to use Roger's stuff)
			void render() const; // perform rendering for current place in game
			void getInput();					//read input and translate
			void take();						//friends functions maybe?
			void use();							//friends functions maybe?
			void look();						//check surroundings
			void move(direction);			//move to a room
			//other functions for game logic (if any)
	};
}

#endif
