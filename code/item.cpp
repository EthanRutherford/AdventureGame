/* item.cpp
 * Project: AdventureGame
 * Owner: Ethan Waddle
 */
#include "item.h"
#include "custom_io.h"
#include <vector>
using namespace std;
using namespace adventure_game;

namespace {
	// manage global item data here
	int next_item_id = 0;
	// dynamic arrays of each of the item kinds
	vector<Item> itemArray;
	vector<Disposable> dispArray;
	vector<Treasure> treaArray;
}

map<string,int> Item::_itemLookupByName;
map<int,string> Item::_itemLookupById;
Item::Item()
{
	ID = next_item_id++;
	consumable = false; // default not-consumable
}
Item::Item(int itemId)
{
	ID = next_item_id++;
	name = item_id_to_name(itemId);
	consumable = false;
}
Item::Item(string itemName)
{
	ID = next_item_id++;
	name = itemName;
	consumable = false;
}
/* static */ bool Item::does_item_exist(string itemName)
{
	return _itemLookupByName.count(itemName) != 0;
}
/* static */ bool Item::does_item_exist(int itemId)
{
	return _itemLookupById.count(itemId) != 0;
}
/* static */ string Item::item_id_to_name(int itemId)
{
	if (_itemLookupById.count(itemId) != 0)
		return _itemLookupById[itemId];
	return string();
}
/* static */ int Item::item_name_to_id(string itemName)
{
	if (_itemLookupByName.count(itemName) != 0)
		return _itemLookupByName[itemName];
	return -1;
}
/* static */ Item* Item::get_global_item(int itemId)
{
	UNREFERENCED_PARAMETER(itemId);
	return NULL; // unimplemented
}
/* static */ Item* Item::get_global_item(string itemName)
{
	UNREFERENCED_PARAMETER(itemName);
	return NULL; // unimplemented
}
void Item::_loadFromMarkup(const tag& tagObj)
{
	UNREFERENCED_PARAMETER(tagObj);
}
void Item::_writeDescription() const
{
}

Disposable::Disposable()
{
}
void Disposable::_writeDescription() const
{
}

Treasure::Treasure()
{
	Value = 0.0;
}
void Treasure::_loadFromMarkup(const tag& tagObj)
{
	UNREFERENCED_PARAMETER(tagObj);
}
void Treasure::_writeDescription() const
{
}
