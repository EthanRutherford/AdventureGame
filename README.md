# Adventure Game Project - CS 230

## Bulletin
(Put stuff here that you want people to see...)

* Note about output: to keep style matching among output, try to portray all information to the user as plain text. Brackets break the immersion. Try to tell the user things in a descriptive way, rather than a bulleted list fashion.

* Note about interface: the game element class supplies a virtual interface which is supposed to be implemented as a private interface. Access modifiers in C++ DO NOT AFFECT virtual function calls. I can have a private virtual in a base class AND STILL override it in a derived. This strategy is preferred because I DO NOT want users calling the virtual methods. They are merely reserved for the implementation. Whenever I prefix a name with an underscore, I basically am saying: "This element is reserved for the implementation of a class and its children." Therefore it should never be called directly. Sorry I didn't make this clearer earlier! You might wonder why I do this? Primarily, it's just me following I practice that I use to make code expandable if need be. Check out [this article](http://www.gotw.ca/publications/mill18.htm), the main point of which is that customizable behavior in a base class SHOULD be seperate from the interface. In the author's opinion, if a virtual function is both interface and customizable the code cannot be expanded later on. Both public and virtual interfaces should be seperate. Furthermore, virtual functions should be made private unless derived classes need to call them. Here's an example:

```cpp
class baseClass
{
public:
	void action() {
		cout << "Do something that I want each object to do regardless of subtype...";
		_action(); // do something that each subtype does differently
	}
private:
	virtual void _action() = 0;
};

class derviedClass : public baseClass
{
private:
	// override base class method - it's private, but still overridable
	virtual void _action() {

	}
};

class otherDerivedClass : public derivedClass
{
public:
	void doSomething()
	{
		// this only allows the object to use the full implementation
		// from baseClass::action
		_action(); // error: is private from derivedClass
	}
};
```

* Please only commit code that compiles! This will allow the people using the Windows build script to not go crazy. When a module compiles, I'll add it to the makefile.
* Place puesdo-code in the root directory (AdventureGame), not AdventureGame/code. Place only things that compile, please!
* Try to include your name in the commit message for readibility.
* If you're getting annoyed prefixing std:: and don't want to pollute a file with using directives, consider using a private or protected member typedef:

```cpp
class myClass
{
	typedef std::string _String;
public:
	_String get_name() const
	{ return "Blaarg"; }
};
```

* Header file format: Use include guards around header files so that they can be ``` #include```d multiple times. Place everything within ```namespace adventure_game { /* ... */ }```. Refer to the following example:

```cpp
// MyHeader.h
#ifndef ADVENTUREGAME_MYHEADER_H // ADVENTUREGAME_NAMEOFHEADERFILE_H
#define ADVENTUREGAME_MYHEADER_H

// header contents here
namespace adventure_game
{
}

#endif
```

## Group Members:
| Member | Email Prefix |
| ------ | ------------ |
| EthanR | epr12a       |
| EthanW | eaw09c       |
| RogerG | rpg11a       |

## Links from Canvas:
[Wikipedia Article](http://en.wikipedia.org/wiki/Colossal_Cave_Adventure)

[Fan Page](http://www.rickadams.org/adventure/)

[Spoiler Hints](http://www.rickadams.org/adventure/d_hints/index.html)

## Division of Labor:
List tasks for each member of the group. Feel free to make changes. I may have forgotten which ones went with whom...
* Ethan R.
	1. objects
	2. player/npcs
	3. game loop
	4. 
* Ethan W.
	1. items
	2. creatures
	3. 
* Roger G.
	1. markup system for adventure text file
	2. room class design
	3. io system design
	4. 

## Draft Assignment Description
* Basic Stuff:
	* Due Thursday, October 24th 2013 by 5am
	* Points 80

* Build a text adventure game similar to the classic Colossal Cave game. Your adventure game must include at least "rooms" and "items". The player of the game should be able to collect, move and "use" items in order to complete the adventure. Actions taken by the player should depend on several factors: which "room" the player is in, what item(s) the player has, what item(s) are in the current "room", and what actions have previously been taken.

* Your design will determine what is possible in the adventure and what is not possible and how you represent the state of the adventure in your objects. For example, say drinking a potion makes the player invisible to the dragon, and therefore changes how a "room" is described or what actions are allowed. In order for this to be a part of the game some object will need to remember whether the player has drunk the potion yet. Should that be the player? or the "room"? or the potion? or something else? Consider that one way to know whether an action has been taken is to leave an "item" in the player's inventory, or in the room's inventory. It could even be an item that doesn't "print out", so the user of the program would not even have to know it was there. Of course that means "items" can be invisible to the user.

* Your solution should include at least the following OO features:

	* data hiding / encapsulation
	* polymorphism / inheritance / "is a"
	* member "has a" relationship with a non-trivial object (Box "has a" left, but double is a trivial type so that wouldn't count)
	* pointer "has a" relationship with a non-trivial object (Polygon "has a" pts, but double[] is a trivial type so that wouldn't count)
	* "knows a" relationship (with a non-trivial, non-owned object)

* Grading criteria / questions for Draft:

	* code compiles and runs?
	* code is organized in headers (.h) and source files (.cpp) correctly?
	* code follows the design you submitted?
	* code includes the OO features described above?
	* code is const correct?
	* code is memory leak free? respects allocation contract?

* Submit zip file containing (all in the "root" of the zip):

	* headers and source files
	* any required data files, optional
	* demo.txt file such that adventure < demo.txt demonstrates interesting features of your game

* I will compile your work using the following:
	- g++ -Wall -std=gnu++0x *.cpp -o adventure

