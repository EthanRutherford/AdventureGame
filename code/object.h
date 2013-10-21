/* object.h
 * Owner: Ethan Rutherford
 * Brief: Interface for objects
 */
#ifndef ADVENTUREGAME_OBJECT_H
#define ADVENTUREGAME_OBJECT_H
#include <string> // just need std::string for header

namespace adventure_game{
	class Object{		//Objects are physical things that exist in (belong to) rooms
		public:
			typedef std::string String; // Ethan doesn't like underscores...
			std::string getName() const {return name;};
			std::string getDesc() const {return desc;};
			virtual ~Object() {};
		protected:
			String name;
			String desc;
	};

	class Aesthetic: public Object{		//as name suggests, merely aesthetic
		public:
			Aesthetic(String Name, String Desc): name(Name), desc(Desc) {};
		private:
			String name, desc;
	};

	class Container: public Object{		//an object that has item(s) in it
		public:
			std::string peek() const;	//see what's inside
			int take();				//take what's inside (and remove from contents)
			bool isEmpty() {return false; /*unimplemented*/}			//is it empty?
			Container();				//figure out initialization later.
			~Container();
		private:
			int* contents;				//contents are item ids
			int size;
	};

	class Interactive: public Object{	//an object that an item can be used on
		public:
			bool isActive() const {return activated;};
			bool activate(int id); //if correct item id, change activated state, return true if correct item
			Interactive();
		private:
			int activatorId;
			bool activated;
			String successMessage;
			String failureMessage;
	};
}

#endif
