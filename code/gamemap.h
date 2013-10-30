/* gamemap.h
 * Project: AdventureGame
 * Owner: Roger Gee
 * Brief: contains the 'room' and 'gamemap' classes
 * which provide functionality for the game's mapping
 * system
 */
#ifndef ADVENTUREGAME_GAMEMAP_H
#define ADVENTUREGAME_GAMEMAP_H
#include <string> // get 'string'
#include <list>
#include "game_element.h"
#include "object.h" // get 'Object' and its sub-types
#include "item.h" // get 'Item'
#include "people.h" // get 'NPC'
#include "creature.h"

namespace adventure_game
{
    enum direction // DO NOT change the order of elements in this enumeration!
    {
        bad_direction = -1,
        north,
        northwest,
        northeast,
        south,
        southwest,
        southeast,
        east,
        west
    };

    direction direction_from_string(const std::string&);
    const char* direction_to_string(direction);

    class room : public game_element
    {
        friend class gamemap;
    public:
        room();
        
        int get_item_count() const; // number of items in the room (including those in containers)
        Item* take_item(const String& item); // if the item with the specified name exists, remove the first occurance and return ptr to item; NULL else on fail

        Interactive& get_door(direction inDir)
        { return _doors[inDir]; }
        const Interactive& get_door(direction inDir) const
        { return _doors[inDir]; }

        Creature* get_creature()
        { return &_creature; }
        const Creature* get_creature() const
        { return &_creature; }
        void check_lives();
        
        // gets the Interactive object that is described by the specified name
        // or returns NULL if none was found
        const Interactive* search_interactive(const String& objName) const;
        Interactive* search_interactive(const String& objName);

        // gets the Item object that is described by the specified name
        // or returns NULL if none was found
        const Item* search_item(const String& objName) const
        { return _roomItems.search_item(objName); }
        Item* search_item(const String& objName)
        { return _roomItems.search_item(objName); }

        // gets the Container object that is described by the specified name
        // or returns NULL if none was found
        const Container* search_container(const String& objName) const;
        Container* search_container(const String& objName);

        // gets the Aesthetic object that is described by the specified name
        // or returns NULL if none was found
        const Aesthetic* search_static(const String& staticName) const;
        Aesthetic* search_static(const String& taticName);
        
        // gets the NPC that is described by the specified name
        // or returns NULL if none was found
        const NPC* search_NPC(const String& NPCName) const;
        NPC* search_NPC(const String& NPCName);
        
        // performs the 'look' operation for any game_element that 
        // matches the specified name; return false if none was found
        bool look_for(const String& obj) const;
    private:
        // gets 'name' from game_element (protected member)
        String _text; // text the user sees when they look at a room

        // rooms adjacent to this room
        // look up by _neighbors[ direction enum value ]
        room* _neighbors[8];
        Interactive _doors[8];

        // implement game_element interface
        virtual void _loadFromMarkup(const tag&);
        virtual void _writeDescription() const; // this is an implementation detail, not an interface function!

        Container _roomItems; // I just used Container as a container for the items!
        std::list<Aesthetic> _statics; // Aesthetic objects in the room
        std::list<Container> _containers; // objects that contain items
        std::list<Interactive> _interactives; // other objects that are in the room
        std::list<NPC> _npcs;
        Creature _creature;
    };

    class gamemap
    {
        typedef std::string String;
    public:
        gamemap(const char* markupFile); // load everything from markup

        bool is_valid_current_room() const
        { return _pCurRoom!=NULL; }
        // get pointer to current room object
        const room* get_current_room() const
        { return _pCurRoom; }
        room* get_current_room()
        { return _pCurRoom; }
        unsigned int get_number_of_rooms() const
        { return _rooms.size(); }

        // prints a description that describes the map to the user
        // probably only going to use this for testing
        void print_status() const;
        void print_story() const; // if the map had a story specified, then it's printed on exCout
        
        bool travel(direction go); // change the current room by walking in the specified direction
        bool can_travel(direction go) const; // determine if a room lies to the specified direction
    private:
        room* _pCurRoom;
        std::list<room> _rooms;
        tag _storyTag; // optional story text

        void _outputStorySubTag(const tag*) const;
    };
}

#endif
