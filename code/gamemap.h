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
    enum direction
    {
        north,
        northwest,
        northeast,
        south,
        southwest,
        southeast,
        east,
        west
    };

    class room : public game_element
    {
        friend class gamemap;
        typedef std::string _String;
    public:
        room();
        ~room();

        int get_item_count() // number of items in the room
        { return _items.size(); }
        bool take_item(_String itemName); // if the item exists, remove it and return true; else return false
    private:
        _String _text; // text the user sees when they look at a room

        // rooms adjacent to this room
        // look up by _neighbors[ direction enum value ]
        room* _neighbors[8];

        // implement game_element interface
        virtual bool _loadFromMarkup(const tag&);
        virtual void _writeDescription() const;

        std::list<int> _items; // ids of items currently in room
        std::list<Object*> _objects; // objects in room
        std::list<NPC> _npcs; // any NPCs in the room
    };

    class gamemap
    {
    public:
        gamemap(const char* markupFile); // load everything from markup
        ~gamemap();

        room* get_current_room() const // get pointer to current room object
        { return _pCurRoom; }
        unsigned int get_number_of_rooms() const
        { return _pRooms.size(); }
        
        bool travel(direction go); // change the current room by walking in the specified direction
        bool can_travel(direction go) const; // determine if a room lies to the specified direction
    private:
        room* _pCurRoom;
        std::list<room*> _pRooms;
        std::list<Item*> _pItems;
    };
}

#endif
