//Ethan W. Design Document
#include <string> // get 'string' type

enum Items {Key, Treasure, Potion}; //This is an example of an enumeration, for disposables, if we so choose to implement disposables that way.  For example, water's effect is QUENCHED, Invisibility Potion's effect is INVISIBLE

// An ITEM is something that can be taken.

class Item
{
	typedef std::string String;
 public:
	Item();
	~Item();
	

	//void setName(String NewX){Name=NewX;}
	
	String getName()const{return Name;}
	int getID{return ID;}
	bool isConsumable{return consumable;}
	
	virtual void useItem();// May or may not implement item usage within to 

private:
`	
	String Name;
	int ID;
	bool consumable; //if it is consumable, we return -1 if it's already used
			 //this means that if an item is not disposable, we return true
			 //if an item is disposable and we have an unused item in our inventory, we return true
	
	};




class Disposable: public Item //potions, etc.
{
 public:
	
	//Ignore Effect for the sake of the demo		
	// Effect getEffect()const {return x}
	// void setEffect(Effect newEff) {x=newEff}
	
	
	void useItem();
	
	bool getStatus()const{return Status;}
	void setStatus(bool newStatus){Status=newStatus;}
	
 private:
	bool Status; //can be initialized to true, meaning can be used.  For example, a potion in inventory that has not been drunk will be true.
	
	//Effect x;
 };




class Treasure: public Item //a Treasure Item has a value
{
 public:
	double getValue()const{return Value;}
 	void setValue(double newValue){Value=newValue;}
	
	void useItem(){}
 private:
	double Value;	
 };

class Key: public Item
{
 public:
	
 private:
	
 }
