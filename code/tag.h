/* tag.h
 * Project: AdventureGame
 * Owner: Roger Gee
 * Brief: contains types that facilitate the input/output of
 * the simple markup language used to represent variable game
 * data.
 */
#ifndef ADVENTUREGAME_TAG_H
#define ADVENTUREGAME_TAG_H
#include "custom_io.h"
#include <list>

namespace adventure_game
{
    class tag
    {
        typedef std::string String;
        typedef std::istream IStream;
        typedef std::list<tag*> List;
        typedef std::list<tag*>::const_iterator ConstIter;
        typedef std::list<tag*>::iterator _Iter;
        typedef std::size_t Uint;
    public:
        tag();
        tag(const tag&);
        ~tag();

        tag& operator =(const tag&);

        const String& get_name() const
        { return _name; }
        const String& get_attribute() const
        { return _attribute; }
        const String& get_content() const
        { return _content; }
        Uint get_position() const
        { return _position; }

        Uint get_number_of_children() const
        { return _childTags.size(); }
        const tag* next_child() const;

        void clear();

        void read(IStream&);
    private:
        String _name;
        String _attribute;
        String _content;
        List _childTags;
        Uint _position;

        mutable ConstIter _iter;
    };

    void output_color_tag(const tag* pColorTag);
}

#endif
