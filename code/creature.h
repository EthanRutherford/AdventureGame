/* creature.h
 * Project: AdventureGame
 * Owner: Ethan Rutherford
 * Brief: Interface for creatures of various types.
 */
#ifndef ADVENTUREGAME_CREATURE_H
#define ADVENTUREGAME_CREATURE_H
#include <string> // get 'string' type
#include "game_element.h"
#include "tag.h" // get 'tag' type

namespace adventure_game{
	class Creature: public game_element{
		public:
			bool isHostile() const {return hostile;}
			int getHealth() const {return health;}
			void takeDamage(int damage);
			int attack();
			void invalidate() {isValidState = false;}
			bool isValid() const {return isValidState;}
			
			Creature();
		protected:
			int power;
			bool hostile;	//determines if creature attacks you. becomes true if you attack a non-hostile
			int health;
			String desc;
		private:
			bool isValidState;

			virtual void _loadFromMarkup(const tag&);
			virtual void _writeDescription() const;
	};
}

#endif
