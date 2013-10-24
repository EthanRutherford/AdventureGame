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
	/* This is a hack...
	 *  Since we want to manage items globally and refer to them by id, I use
	 *  this unloader class to manage dynamically allocated 'Item' objects. They are
	 *  are stored in dynamic arrays (std::vectors) and unload when the vector destroys its
	 *  elements for the final time. To prevent the Item objects being destroyed prematurely
	 *  when the dynamic array resizes, I add copy functionality that passes ownership of the
	 *  Item* to the new Unloader object. This system ensures that each Item object exists for 
	 *  the entire duration of whatever happens in the 'main' function. I CANNOT make guarantees
	 *  for how the items will be unloaded after main has returned. Therefore, let's not have any 
	 *  other global objects!
	 */
	template<typename T>
	class Unloader
	{
	public:
		Unloader(T* element)
		{
			_elem = element;
		}
		Unloader(const Unloader& obj)
		{
			// pass ownership
			_elem = obj._elem;
			obj._elem = NULL;
		}
		~Unloader()
		{
			if (_elem != NULL)
				delete _elem;
		}

		Unloader& operator =(const Unloader& obj)
		{
			// pass ownership
			_elem = obj._elem;
			obj._elem = NULL;
			return *this;
		}
	private:
		mutable T* _elem;
	};

	
	vector< Unloader<Item> > globalItems;
	// TODO: add sub item types
}

Item::Item()
{
	consumable = false; // default not-consumable
}
Item::Item(const Item& obj)
{
	// copy anything here
	name = obj.name;
	description = obj.description;
	consumable = obj.consumable;

}
void Item::_loadFromMarkup(const tag& tagObj)
{
	// An item expects the following tags:
	// <name> -name of item i.e. Potion
	// <desc> -description of tag
	// <consume>true|false -optional consumable flag value
	const tag* pNext = tagObj.next_child();
	if ( tagObj.get_attribute().length() > 0 )
		name = tagObj.get_attribute();
	while (pNext != NULL)
	{
		const string& tagName = pNext->get_name();
		if (tagName == "name")
			name = pNext->get_attribute().length()==0 ? pNext->get_content() : pNext->get_attribute();
		else if (tagName == "desc")
			description = pNext->get_attribute().length()==0 ? pNext->get_content() : pNext->get_attribute();
		else if (tagName == "consume")
			consumable = pNext->get_attribute().length()>0 ? pNext->get_attribute()=="true" : pNext->get_content()=="true";
		pNext = tagObj.next_child();
	}
}
void Item::_writeDescription() const
{
	exCout << consolea_fore_blue << name << consolea_normal << ": " << description;
}

Item* adventure_game::create_item(const tag& tagObj)
{
	Item* newItem = new Item;
	newItem->load(tagObj);
	globalItems.push_back(newItem); // the item (and its memory) will be managed in another context
	return newItem;
}
Item* adventure_game::create_item(Item* pItem)
{
	// create new item based off of pre-existing by ptr to Item object
	Item* newItem = new Item(*pItem);
	globalItems.push_back(newItem);
	return newItem;
}
/*
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
*/
