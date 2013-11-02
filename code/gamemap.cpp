/* gamemap.cpp
 * Project: Adventure Game
 * Owner: Roger Gee
 */
#include "gamemap.h"
#include "custom_io.h"
#include <fstream>
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

status adventure_game::status_from_string(const std::string& in)
{
	if (in == "normal")
		return normal;
	if (in == "dark")
		return dark;
	if (in == "flooded")
		return flooded;
	if (in == "hidden")
		return hidden;
	return bad_status;
}
const char* adventure_game::status_to_string(status in)
{
	switch (in)
	{
	case normal:
		return "normal";
	case dark:
		return "dark";
	case flooded:
		return "flooded";
	case hidden:
		return "hidden";
	default:
		return "bad status";
	}
	return "";
}

room::room()
{
    for (int i = 0;i<8;i++)
        _neighbors[i] = NULL;
	state = normal;
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
void room::check_lives()
{
    for (list<NPC>::iterator iter = _npcs.begin(), end = _npcs.end();iter!=end;iter++)
        if (iter->getHealth() <= 0)
        {
            exCout << consolea_fore_white << iter->get_name() << consolea_normal << " has died.\n";
            _npcs.erase(iter);
            return;
        }
    if (_creature.isValid() && _creature.getHealth() <= 0)
    {
        exCout << consolea_fore_white << _creature.get_name() << consolea_normal << " has died.\n";
        _creature.invalidate();
    }
}
const Interactive* room::search_interactive(const string& objName) const
{
	for (list<Interactive>::const_iterator iter = _interactives.begin(), end = _interactives.end();iter!=end;iter++)
        if ( iter->compare_name(objName) )
            return &(*iter);
    for (int i = 0;i < 8;i++)
        if ( _doors[i].compare_name(objName) )
            return &_doors[i];
    return NULL;

}
Interactive* room::search_interactive(const string& objName)
{
    for (list<Interactive>::iterator iter = _interactives.begin(), end = _interactives.end();iter!=end;iter++)
        if ( iter->compare_name(objName) )
            return &(*iter);
    for (int i = 0;i < 8;i++)
        if ( _doors[i].compare_name(objName) )
            return &_doors[i];
    return NULL;

}
const Container* room::search_container(const string& objName) const
{
    for (list<Container>::const_iterator iter = _containers.begin(), end = _containers.end();iter!=end;iter++)
        if ( iter->compare_name(objName) )
            return &*iter;
    return NULL;
}
Container* room::search_container(const string& objName)
{
    for (list<Container>::iterator iter = _containers.begin(), end = _containers.end();iter!=end;iter++)
        if ( iter->compare_name(objName) )
            return &*iter;
    return NULL;
}
const NPC* room::search_NPC(const string& NPCName) const
{
    for (list<NPC>::const_iterator iter = _npcs.begin(), end = _npcs.end();iter!=end;iter++)
        if ( iter->compare_name(NPCName) )
            return &*iter;
    return NULL;
}
NPC* room::search_NPC(const string& staticName)
{
	for (list<NPC>::iterator iter = _npcs.begin(), end = _npcs.end();iter!=end;iter++)
        if ( iter->compare_name(staticName) )
            return &*iter;
    return NULL;
}
const Aesthetic* room::search_static(const string& staticName) const
{
    for (list<Aesthetic>::const_iterator iter = _statics.begin(), end = _statics.end();iter!=end;iter++)
        if ( iter->compare_name(staticName) )
            return &*iter;
    return NULL;
}
Aesthetic* room::search_static(const string& NPCName)
{
    for (list<Aesthetic>::iterator iter = _statics.begin(), end = _statics.end();iter!=end;iter++)
        if ( iter->compare_name(NPCName) )
            return &*iter;
    return NULL;
}
bool room::look_for(const string& objName) const
{
    // Polymorphism!!!
    const game_element* pElem;
    // try interactives
    pElem = search_interactive(objName);
    if (pElem != NULL)
    {
        pElem->look();
        return true;
    }
    pElem = search_item(objName);
    if (pElem != NULL)
    {
        pElem->look();
        return true;
    }
    const Container* box = search_container(objName);
    if (box != NULL)
    {
        if (!box->isLocked())
            exCout << "Inside the " << consolea_fore_yellow << box->get_name() << consolea_normal << " you find "; 
        box->look();
        if (!box->isLocked())
            exCout << endl;
        return true;
    }
    pElem = search_NPC(objName);
    if (pElem != NULL)
    {
        pElem->look();
        return true;
    }
    pElem = search_static(objName);
    if (pElem != NULL)
    {
        pElem->look();
        return true;
    }
    if ( _creature.isValid() )
    {
        _creature.look();
        return true;
    }
    return false;
}
void room::interact(Interactive* object)
{
	if (object->getRoomName().length() > 0)
		_linkedRooms[object->getRoomName()]->resetStatus();
}
void room::_loadFromMarkup(const tag& tagObj) // assume that tagObj has name "room"
{
    /* A room has the following supported tags that are handled here:
     *  <name> -required
     *  <text> -required
     *  <door> -optional ex. <door direction> <name>TheDoor</name> <activator Key/> <desc>It stops you from walking!</desc> </door> --lookup performed by string comparison
     *  <object> -any number or zero (these are interactives)
     *  <static> -any number or zero (these are asthetics)
     *  <npc) -any number or zero
     *  <item> -any number or zero
     *  <creature> -one or none
     *  <container> -see container markup load documentation
     *  tags in a <room> tag but not supported here
     *  <direction> -where direction is north, south, east, west, northeast,
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
            _roomItems.setName(name);
            if (name.length() == 0)
                cerr << "Error: name for room cannot be empty\n";
        }
        else if (tagName == "text")
        {
            // only use tag content
            _text = pSubTag->get_content();
        }
        else if (tagName == "item")
            _roomItems.put( Item::create_item(*pSubTag) );
        else if (tagName == "container")
        {
            _containers.emplace_back();
            _containers.back().load(*pSubTag);
        }
        else if (tagName == "object")
        {
            _interactives.emplace_back();
            _interactives.back().load(*pSubTag);
        }
        else if (tagName == "door")
        {
            direction d = direction_from_string( pSubTag->get_attribute() );
            if (d == bad_direction)
                cerr << "Error: expected direction specifier for <door> tag\n";
            _doors[d].load(*pSubTag);
        }
        else if (tagName == "static")
        {
            _statics.emplace_back();
            _statics.back().load(*pSubTag);
        }
        else if (tagName == "npc")
        {
            _npcs.emplace_back();
            _npcs.back().load(*pSubTag);
        }
        else if (tagName == "creature")
            _creature.load(*pSubTag);
		else if (tagName == "state")
			state = pSubTag->get_attribute().length()==0 ? status_from_string(pSubTag->get_content()) : status_from_string(pSubTag->get_attribute());
        pSubTag = tagObj.next_child();
    }
}
void room::_writeDescription() const
{
	if (state == dark)
		exCout << "It's so dark you can't see anything... You must turn back.\n";
    else if (_creature.isValid() && _creature.isHostile())
	// write the room description to exCout
        exCout << _text << " " << "There's a " << consolea_fore_white << consolea_normal << _creature.get_name() << " here!\n";
	else
    {
        exCout << _text << ' ';
		//list aesthetics.
        if ( _statics.size()>0 )
        {
            exCout << "There is ";
            for (list<Aesthetic>::const_iterator iter = _statics.begin(), n = _statics.end(), end = n--;iter!=end;iter++)
            {
                if (_statics.size() == 1 && _interactives.size() == 0)
                    exCout << "a " << iter->get_name() << ". ";
                else if (iter == n && _interactives.size() == 0)
                    exCout << "and a " << iter->get_name() << ". ";
                else
                    exCout << "a " << iter->get_name() << ", ";
            }
        }
        //list interactives
        if ( _interactives.size()>0 )
        {
            if ( _statics.size()==0 )
                exCout << "There is ";
            for (list<Interactive>::const_iterator iter = _interactives.begin(), n = _interactives.end(), end = n--;iter!=end;iter++)
            {
                if (_interactives.size() == 1)
                    exCout << "a " << consolea_fore_blue << iter->get_name() << consolea_normal << ". ";
                else if (iter == n)
                    exCout << "and a " << consolea_fore_blue << iter->get_name() << consolea_normal << ". ";
                else
                    exCout << "a " << consolea_fore_blue << iter->get_name() << consolea_normal << ", ";
            }
        }
        //as well as containers
        if ( _containers.size()>0 )
        {
            exCout << "You can see ";
            for (list<Container>::const_iterator iter = _containers.begin(), n = _containers.end(), end = n--;iter!=end;iter++)
            {
                if (_containers.size() == 1)
                    exCout << "a " << consolea_fore_yellow << iter->get_name() << consolea_normal << ". ";
                else if (iter == n)
                    exCout << "and a " << consolea_fore_yellow << iter->get_name() << consolea_normal << ". ";
                else
                    exCout << "a " << consolea_fore_yellow << iter->get_name() << consolea_normal << ", ";
            }
        }
        if (state != flooded)
		{
			// available places to go
			exCout << "Looking around, you see that ";
			for (int i = 0;i<8;i++)
			{
				if (_neighbors[i] != NULL and _neighbors[i]->getStatus() != hidden)
				{
					if ( _doors[i].has_activator() && !_doors[i].isActive() )
						exCout << "the way " << consolea_fore_magenta << direction_to_string( direction(i) ) << consolea_normal << " is barred by the " << consolea_fore_cyan << _doors[i].get_name() << consolea_normal << ", ";
					else
					{
						exCout << "you can go ";
						highlight( direction_to_string( direction(i) ),consolea_fore_magenta);
						exCout << " to enter the ";
						highlight(_neighbors[i]->name,consolea_fore_cyan);
						exCout << ", ";
					}
				}
			}
			exCout << "and ";
			// items
			if ( _roomItems.getCount() > 0 )
			{
				exCout << "lying about is ";
				_roomItems.look();
			}
			else
				exCout << "there are no items to be found.";
			// npcs
			if ( _npcs.size()>0 )
			{
				exCout << " Nearby you see ";
				for (list<NPC>::const_iterator iter = _npcs.begin(), n = _npcs.end(), end = n--;iter!=end;iter++)
				{
					if (_npcs.size() == 1)
						exCout << consolea_fore_white << iter->get_name() << consolea_normal << ". ";
					else if (iter == n)
						exCout << "and " << consolea_fore_white << iter->get_name() << consolea_normal << ". ";
					else
						exCout << consolea_fore_white << iter->get_name() << consolea_normal << ", ";
				}
			}
        }
		if (state == flooded)
			exCout << "It is flooded to the point you can't navigate. You must go back the way you came.";
		exCout << endl;
    }
}
gamemap::gamemap(const char* markupFile)
{
    _pLastRoom = NULL;
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
            else if (theTag.get_name() == "story") // expect 1, overwrite if found more than 1
            {
                // TODO: attribute could be used for story title
                _storyTag = theTag;
            }
        } while ( markupStream.good() );
        // handle late-bound room associations
        while ( !roomMapping.empty() )
        {
            RoomMapElement& elem = roomMapping.front();
            for (int d = 0;d<=7;d++)
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
		// handle late-bound interactive room pointer binding
		for (list<room>::iterator rIter = _rooms.begin(), rEnd = _rooms.end();rIter!=rEnd;rIter++)
			for (list<Interactive>::iterator iter = rIter->_interactives.begin(), end = rIter->_interactives.end();iter!=end;iter++)
				rIter->_linkedRooms[iter->getRoomName()] = loadedRooms[iter->getRoomName()];
		// TODO: later might look for global <start-room> tag
        if (_rooms.size() > 0)
            _pCurRoom = &_rooms.front();
        else
            _pCurRoom = NULL;
    }
    else
        _pCurRoom = NULL;
}
void gamemap::print_status() const
{
    // for testing purposes
    exCout << "Current Room: [";
    if (_pCurRoom == NULL)
        exCout << consolea_fore_red << "!An undetermined location!" << consolea_normal;
    else
        exCout << consolea_fore_blue << _pCurRoom->get_name() << consolea_normal;
    exCout << "]\nAvailable locations from here:\n";
    for (int i = 0;i<8;i++)
    {
        if (_pCurRoom->_neighbors[i] != NULL)
            exCout << "\t" << consolea_fore_red << direction_to_string( direction(i) ) << consolea_normal << ": " << consolea_fore_blue << _pCurRoom->_neighbors[i]->get_name() << consolea_normal << endl;
    }
}
void gamemap::print_story() const
{
    int childCnt = _storyTag.get_number_of_children();
    const tag* pChild = _storyTag.next_child();
    string storyText;
    const string storyContent = _storyTag.get_content();
    for (size_t i = 0;i<storyContent.length();i++)
    {
        if (pChild!=NULL && pChild->get_position()==i)
        {
            exCout << storyText;
            storyText.clear();
            // expect color tag
            output_color_tag(pChild);
            pChild = _storyTag.next_child();
        }
        storyText.push_back( storyContent[i] );
    }
    exCout << storyText;
    // get any sub-tags that append content
    while (pChild != NULL)
    {
        output_color_tag(pChild);
        pChild = _storyTag.next_child();
    }
    exCout << endl;
}
bool gamemap::travel(direction go)
{
    if (_pCurRoom!=NULL && _pCurRoom->_neighbors[go]!=NULL)
    {
        if ( _pCurRoom->_doors[go].has_activator() && !_pCurRoom->_doors[go].isActive() )
            return false;
		_pLastRoom = _pCurRoom;
        _pCurRoom = _pCurRoom->_neighbors[go];
        return true;
    }
    return false;
}
bool gamemap::travel(const string& roomName)
{
    if (_pCurRoom != NULL)
    {
        for (int i = 0;i<=7;i++)
            if ( _pCurRoom->_neighbors[i]!=NULL && _pCurRoom->_neighbors[i]->compare_name(roomName))
                if ( travel( direction(i) ) )
                    return true;
    }
    return false;
}
bool gamemap::can_travel(direction go) const
{
    // is there a room in the specified direction
	if (_pCurRoom->_neighbors[go]!=NULL && _pCurRoom->_neighbors[go]->getStatus() == hidden)
		return false;
    return _pCurRoom!=NULL && _pCurRoom->_neighbors[go]!=NULL;
}
bool gamemap::can_travel(const string& roomName) const
{
    // is there a room in the specified room
    if (_pCurRoom != NULL)
    {
        for (int i = 0;i<=7;i++)
            if ( _pCurRoom->_neighbors[i]!=NULL && _pCurRoom->_neighbors[i]->compare_name(roomName) )
                return true;
    }
    return false;
}
