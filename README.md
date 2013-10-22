# Adventure Game Project - CS 230

## Bulletin
(Put stuff here that you want people to see...)
* Roger, read this: my idea for the item array works like this: we have an item array, containing every item to be in the game. The index in the array is the item ID. When we get input, the string is translated into int by finding the item with matching name (case insensitive) by the game class. Then, we pass IDs to the room, or the player (depending on the function we are using) and the player and room don't do further lookups, they merely use the id. Their int arrays for numItems have the same idea: the index of the array is the id. that way, we simply can check value at numItems[id] and go on from there. If items interact with objects the way I've written objects, then the object needs nothing from item except the id, which has been translated by game already. If you think they need to work differently, do that, and make it work, I don't have a problem with that, so long as it all works, this is just the way I was thinking about it.
* Message for EthanR: I've almost finished implementing items. I made a bunch of different changes. Items are managed in the item module. Every game element (Person, Object, Room, ETC.) refers to an item via its ID. You can query the name of the item via a static interface in the Item class. If you later need a pointer to the actual item, you can do several things:
	1. Get a plain old Item* (if one exists) for the name/id (you can query with either name or id)
	2. Query to see if the id/name matches a sub-type of Item (like Disposable or Treasure), in which case you can get a Treasure* or Disposable*
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

