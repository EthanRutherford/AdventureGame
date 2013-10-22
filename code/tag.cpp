/* tag.cpp
 * Project: AdventureGame
 * Owner: Roger Gee
 */
#include "tag.h"
using namespace std;
using namespace adventure_game;

tag::tag()
{
    _position = 0;
    _iter = _childTags.begin();
}
tag::~tag()
{
    for (_Iter i = _childTags.begin(), e = _childTags.end();i!=e;i++)
        delete *i;
}
const tag* tag::next_child() const
{
    if (_iter != _childTags.end())
        return *_iter++;
    _iter = _childTags.begin();
    return NULL;
}
void tag::clear()
{
    _name.clear();
    _attribute.clear();
    _content.clear();
}
void tag::read(istream& stream)
{
    char c;
    clear();
    // read until open tag
    do {
        c = stream.get();
        if (c == '<')
            break;
    } while ( stream.good() );
    // read tag name
    while ( stream.good() )
    {
        c = stream.get();
        if (c == '>')
            break;
        if (c == ' ')
        {
            // read tag attribute
            while ( stream.good() )
            {
                c = stream.get();
                if (c == '>')
                    break;
                if (c=='/' && stream.peek()=='>')
                {
                    stream.get(); // pop off >
                    return; // shorthand with attribute
                }
                _attribute.push_back(c);
            }
            break;
        }
        if (c=='/' && stream.peek()=='>')
        {
            stream.get(); // pop off >
            return; // shorthand
        }
        _name.push_back(c);
    }
    // read tag content
    while ( stream.good() )
    {
        c = stream.get();
        if (c == '<')
        {
            if (stream.peek() != '/')
            {
                // read sub (child) tag
                tag* child = new tag;
                stream.putback(c);
                child->read(stream);
                _childTags.push_back(child);
            }
            else
            {
                string endTag;
                stream.get(); //pop off /
                while ( stream.good() )
                {
                    c = stream.get();
                    if (c == '>')
                        break;
                    endTag.push_back(c);
                }
                if (endTag != _name)
                    cerr << "Error: expected end-tag with name '" << _name << "'; found end tag with name '" << endTag << "'\n";
                break;
            }
        }
        _content.push_back(c);
    }
}
