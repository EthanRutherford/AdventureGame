/* tag.h
 * Project: AdventureGame
 * Owner: Roger Gee
 * Brief: contains types that facilitate the input/output of
 * the simple markup language used to represent variable game
 * data.
 */
#ifndef ADVENTUREGAME_TAG_H
#define ADVENTUREGAME_TAG_H
#include <iostream>
#include <list>

namespace adventure_game
{
    class tag
    {
        typedef std::string _String;
        typedef std::list<tag*> _List;
    public:
        tag();
        tag(const _String& name);
        tag(const _String& name,const _String& content);
        tag(const _String& name,const _String& content,const _String& attribute);
        ~tag();

    private:
        _String _name;
        _String _attribute;
        _String _content;
        _List _childTags;
        unsigned int _position;
    };
}

#endif
