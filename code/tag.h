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
        typedef std::string _String;
        typedef std::istream _Istream;
        typedef std::list<tag*> _List;
        typedef std::list<tag*>::const_iterator _ConstIter;
        typedef std::list<tag*>::iterator _Iter;
        typedef std::size_t _SizeT;
    public:
        tag();
        ~tag();

        const _String& get_name() const
        { return _name; }
        const _String& get_attribute() const
        { return _attribute; }
        const _String& get_content() const
        { return _content; }

        _SizeT get_number_of_children() const
        { return _childTags.size(); }
        const tag* next_child() const;

        void clear();

        void read(_Istream&);
    private:
        _String _name;
        _String _attribute;
        _String _content;
        _List _childTags;
        _SizeT _position;

        mutable _ConstIter _iter;
    };
}

#endif
