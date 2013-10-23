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
#include "game_element.h" // gets tag.h
#include "object.h" // get 'Object' and its sub-types
#include "item.h" // get 'Item'
#include "people.h" // get 'NPC'

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
        typedef std::string String;
    public:
        room();

        int get_item_count() const; // number of items in the room (including those in containers)
        bool take_item(int itemId); // if the item exists, remove it and return true; else return false
    private:
        // gets 'name' from game_element (protected member)
        String _text; // text the user sees when they look at a room

        // rooms adjacent to this room
        // look up by _neighbors[ direction enum value ]
        room* _neighbors[8];

        // implement game_element interface
        virtual void _loadFromMarkup(const tag&);
        virtual void _writeDescription() const;

        Container _roomItems; // I just used Container as a container for the items!
        std::list<Aesthetic> _statics; // Aesthetic objects in the room
        std::list<Container> _containers; // objects that contain items
        std::list<Interactive> _interactives; // other objects that are in the room
        std::list<NPC> _npcs;
    };

    class gamemap
    {
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
        
        bool travel(direction go); // change the current room by walking in the specified direction
        bool can_travel(direction go) const; // determine if a room lies to the specified direction
    private:
        room* _pCurRoom;
        std::list<room> _rooms;
    };
}

#endif
