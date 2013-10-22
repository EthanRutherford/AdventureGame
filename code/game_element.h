/* game_element.h
 * Project: AdventureGame
 * Owner: Roger Gee
 * Brief: contains a simple interface for managing the different
 * elements used in the adventure game
 */
#ifndef ADVENTUREGAME_ELEMENT_H
#define ADVENTUREGAME_ELEMENT_H
#include <string>
#include "tag.h"

namespace adventure_game
{
    /* game_element
     *  An element is any object in the game that:
     *   A) the user interacts with
     *   B) is loaded up from markup (specific instantiations)
     */
    class game_element
    {
        typedef std::string _String;
    public:
        bool load(const tag& t)
        { return _loadFromMarkup(t); }
        void look() const
        { return _writeDescription(); }
        _String name() const
        { return _name; }
    protected:
        _String _name;
    private:
        // implement this interface
        virtual bool _loadFromMarkup(const tag&) = 0;
        virtual void _writeDescription() const = 0;
    };
}

#endif
