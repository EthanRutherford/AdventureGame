//Ethan W. Design Document
#include <string> // get 'string' type

enum Effect {INVISIBLE, FIREPROOF, CURED, QUENCHED, LIT}; //This is an example of an enumeration, for disposables, if we so choose to implement disposables that way.  For example, water's effect is QUENCHED, Invisibility Potion's effect is INVISIBLE

class Item
{
	typedef std::string String;
 public:
	Item();
	~Item();
	
	virtual bool can_take_()const
	{return true;}	

	void setName(String NewX){Name=NewX;}
	
	String getName()const{return Name;}
	
	virtual void useItem();// May or may not implement item usage within to 

private:
	
	String Name;
	
	};




class Disposable: public Item //potions, etc.
{
 public:
			
	Effect getEffect()const {return x}
	void setEffect(Effect newEff) {x=newEff}
	
	
	void useItem();
	
	bool getStatus()const{return Status;}
	void setStatus(bool newStatus){Status=newStatus;}
	
 private:
	bool Status; //can be initialized to true, meaning can be used.  For example, a potion in inventory that has not been drunk will be true.
	
	Effect x;
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
