#include "gamemap.h"
#include "custom_io.h"
#include <fstream>
#include <map>
#include <queue>
using namespace std;
using namespace adventure_game;

namespace {
    // helpers
    typedef struct {
        room* originRoomPtr;
        string adjacentRoomNames[8]; // up to 8 directions
    } RoomMapElement;
    inline
    void highlight(const char* pc,console_attribute ca)
    {
        exCout << ca << pc << consolea_normal;
    }
    inline
    void highlight(const string& rs,console_attribute ca)
    {
        exCout << ca << rs << consolea_normal;
    }
}

direction adventure_game::direction_from_string(const string& s)
{
    if (s == "north")
        return north;
    else if (s == "south")
        return south;
    else if (s == "east")
        return east;
    else if (s == "west")
        return west;
    else if (s == "northeast")
        return northeast;
    else if (s == "northwest")
        return northwest;
    else if (s == "southeast")
        return southeast;
    else if (s == "southwest")
        return southwest;
    return bad_direction;
}
const char* adventure_game::direction_to_string(direction d)
{
    switch (d)
    {
    case north:
        return "north";
    case south:
        return "south";
    case east:
        return "east";
    case west:
        return "west";
    case northeast:
        return "northeast";
    case northwest:
        return "northwest";
    case southeast:
        return "southeast";
    case southwest:
        return "southwest";
    default:
        return "bad direction";
    }
    return "";
}

room::room()
{
    for (int i = 0;i<8;i++)
        _neighbors[i] = NULL;
}
int room::get_item_count() const
{
    int cnt = _roomItems.getCount();
    for (list<Container>::const_iterator i = _containers.begin(), e = _containers.end();i!=e;i++)
        cnt += i->getCount();
    return cnt;
}
Item* room::take_item(const string& itemName)
{
    // attempt to take from non-container items
    Item* r = _roomItems.take(itemName);
    if (r == NULL)
    {
        // search through each container in the room for specified item
        // perform a linear search
        list<Container>::iterator iter = _containers.begin(), end = _containers.end();
        while (iter != end)
        {
            r = iter->take(itemName);
            if (r != NULL)
                return r;
            iter++;
        }
        return NULL;
    }
    return r;
}
void room::_loadFromMarkup(const tag& tagObj) // assume that tagObj has name "room"
{
    /* A room has the following supported tags that are handled here:
     *  <name> -required
     *  <text> -required
     *  <object> -any number or zero
     *  <item> -any number or zero
     * tags in a <room> tag but not supported here
     * <direction> -where direction is north, south, east, west, northeast,
     *  northwest, southeast, southwest - these tags are not handled in this
     *  routine, but rather by the gamemap load routines
     */
    const tag* pSubTag = tagObj.next_child();
    while (pSubTag != NULL)
    {
        const string& tagName = pSubTag->get_name();
        if (tagName == "name")
        {
            if (name.length() != 0)
                cerr << "Warning: multiple names found in room markup for room '" << name << "'; using most recent\n";
            name = pSubTag->get_attribute().length()==0 ? pSubTag->get_content() : pSubTag->get_attribute();
            if (name.length() == 0)
                cerr << "Error: name for room cannot be empty\n";
        }
        else if (tagName == "text")
        {
            // only use tag content
            _text = pSubTag->get_content();
        }
        pSubTag = tagObj.next_child();
    }
}
void room::_writeDescription() const
{
    // write the room description to exCout
    exCout << "Room: " << consolea_fore_blue << name << consolea_normal << "! " << _text << '\n';
    // items, people, etc.
    // available places to go
    exCout << "Places to go:\n";
    for (int i = 0;i<8;i++)
    {
        if (_neighbors[i] != NULL)
        {
            exCout << "\tGo <";
            highlight( direction_to_string( direction(i) ),consolea_fore_blue);
            exCout << "> to enter ";
            highlight(_neighbors[i]->name,consolea_fore_magenta);
            exCout.put('\n');
        }
    }
}

gamemap::gamemap(const char* markupFile)
{
    ifstream markupStream(markupFile);
    if (markupStream)
    {
        map<string,room*> loadedRooms;
        queue<RoomMapElement> roomMapping;
        do {
            tag theTag;
            theTag.read(markupStream);
            if (theTag.get_name() == "room") // add a new room
            {
                _rooms.emplace_back();
                room& newRoom = _rooms.back();
                newRoom.load(theTag); // let the room load what it can from the tag
                if ( loadedRooms.count(newRoom.get_name()) )
                    cerr << "Error: room '" << newRoom.get_name() << "' already exists and has been defined again\n";
                else // associate ptr to room with name for later direction binding
                    loadedRooms[newRoom.get_name()] = &newRoom;
                // find any adjacencies via direction tags
                const tag* pTag = theTag.next_child();
                RoomMapElement rmElem;
                rmElem.originRoomPtr = NULL;
                while (pTag != NULL)
                {
                    direction d = direction_from_string( pTag->get_name() );
                    if (d != bad_direction) // only handle valid direction tags
                    {
                        string name = pTag->get_content();
                        if (name.length() == 0)
                            name = pTag->get_attribute();
                        if (name.length() == 0)
                            cerr << "Error: expected direction tag for room to have target name\n";
                        if ( loadedRooms.count(name) )
                            newRoom._neighbors[d] = loadedRooms[name];
                        else
                        {
                            // add room association for the specified direction
                            rmElem.originRoomPtr = &newRoom; // flag that it's used
                            rmElem.adjacentRoomNames[d] = name;
                        }
                    }
                    pTag = theTag.next_child();
                }
                // if any "late-bindings" have to be made,
                // queue them up for later
                if (rmElem.originRoomPtr != NULL)
                    roomMapping.push(rmElem);
            }
            // handle other tags that exist at file scope
        } while ( markupStream.good() );
        // handle late-bound room associations
        while ( !roomMapping.empty() )
        {
            RoomMapElement& elem = roomMapping.front();
            for (direction d = north;d <= west;++(int&)d)
            {
                if ( elem.adjacentRoomNames[d].length()==0 )
                    continue; // none specified in given direction
                if ( !loadedRooms.count(elem.adjacentRoomNames[d]) )
                {
                    cerr << "Error: room '" << elem.originRoomPtr->get_name() << "' was mapped to non-existent room '" << elem.adjacentRoomNames[d] << "'\n";
                    continue;
                }
                // perform the association
                elem.originRoomPtr->_neighbors[d] = loadedRooms[elem.adjacentRoomNames[d]];
            }
            roomMapping.pop();
        }
        // TODO: later might look for global <start-room> tag
        if (_rooms.size() > 0)
            _pCurRoom = &_rooms.front();
        else
            _pCurRoom = NULL;
    }
    else
    {
        cerr << "Error: could not open companion markup file!\n";
        _pCurRoom = NULL;
    }
}
void gamemap::print_status() const
{
    // this should be called each rendering frame
    exCout << "Current Room: [";
    if (_pCurRoom == NULL)
        exCout << consolea_fore_red << "!An undetermined location!" << consolea_normal;
    else
        exCout << consolea_fore_blue << _pCurRoom->get_name() << consolea_normal;
    exCout << "]\nAvailable locations from here:\n";
    for (int i = 0;i<8;i++)
    {
        if (_pCurRoom->_neighbors[i] != NULL)
            exCout << "\t" << consolea_fore_red << direction_to_string( direction(i) ) << consolea_normal << ": " << consolea_fore_blue << _pCurRoom->_neighbors[i]->get_name() << consolea_normal << '\n';
    }
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
