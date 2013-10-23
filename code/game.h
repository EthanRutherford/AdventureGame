/* game.h
 * Owner: Ethan Rutherford
 * Brief: interface for Game, manages everything
 */
#ifndef ADVENTUREGAME_GAME_H
#define ADVENTUREGAME_GAME_H
#include "custom_io.h" // get iostream types and 'direction' enum type
#include "gamemap.h" // get class 'gamemap'
#include "people.h" // get class 'Player'
#include "item.h"
#include "gamemap.h"

namespace adventure_game{
	class Game{		//manages game data.. not sure what all needs to be in here yet
		public:
			void run();		//runs the game
			Game();
			~Game();
		private:
			Player player;
			gamemap map;						//managed the rooms of the game world
			std::string help;					//contents of help
			bool gameover;
		
			// let's just always use the 'exCout' stream object declared in custom_io.h
			// which is #included into this class's implementation file
			void render() const; // perform rendering for current place in game
			void getInput();					//read input and translate
			void take();				
			void use();					
			void look();						//check surroundings
			void move(direction);				//move to a room
			//other functions for game logic (if any)
	};
}

#endif
