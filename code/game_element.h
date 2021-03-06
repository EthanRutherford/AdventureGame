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
    protected:
        typedef std::string String;
    public:
        void load(const tag& t)
        { _loadFromMarkup(t); }
        void look() const
        { _writeDescription(); }
        String get_name() const
        { return name; }

        bool compare_name(const String& elementName) const;
    protected:
        String name;
    private:
        // implement this interface, which is called by the public
        // interface of this class; these SHOULD NOT be called directly;
        // they are reserved for the implementation
        virtual void _loadFromMarkup(const tag&) = 0;
        virtual void _writeDescription() const = 0;
    };
}

#endif
