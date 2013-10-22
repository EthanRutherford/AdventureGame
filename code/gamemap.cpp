#include "gamemap.h"
#include "custom_io.h"
#include "game.h"
#include <fstream>
using namespace std;
using namespace adventure_game;

room::room()
{
    for (int i = 0;i<8;i++)
        _neighbors[i] = NULL;
}
room::~room()
{
    for (list<Object*>::iterator i = _objects.begin(), e = _objects.end();i != e;i++)
        delete *i;
}
bool room::take_item(string itemName)
{
    // perform a linear search
    list<int>::iterator i = _items.begin();
    list<int>::iterator e = _items.end();
    while (i != e)
    {
        Item* pItem = Game::getItem(*i);
        if ( pItem!=NULL && pItem->getName()==itemName )
        {
            _items.erase(i);
            return true;
        }
        i++;
    }
    return false;
}
bool room::_loadFromMarkup(const tag& tagObj)
{
    /* A room has the following supported tags:
     *  <name> -required
     *  <text> -required
     *  <object>
     *  <item>
     */
    if (tagObj.get_name() == "room")
    {
        
    }
    return false;
}
void room::_writeDescription() const
{
    // write the room description to exCout

}

gamemap::gamemap(const char* markupFile)
{
    _pCurRoom = NULL;
    UNREFERENCED_PARAMETER(markupFile);
}
gamemap::~gamemap()
{
    for (list<room*>::iterator i = _pRooms.begin(), e = _pRooms.end();i!=e;i++)
        delete *i;
}
bool gamemap::travel(direction go)
{
    if (_pCurRoom!=NULL && _pCurRoom->_neighbors[go]!=NULL)
    {
        _pCurRoom = _pCurRoom->_neighbors[go];
        return true;
    }
    return false;
}
bool gamemap::can_travel(direction go) const
{
    return _pCurRoom!=NULL && _pCurRoom->_neighbors[go]!=NULL;
}
