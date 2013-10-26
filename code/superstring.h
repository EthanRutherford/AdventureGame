#include <iostream>
#include <list>
#include "custom_io.h"
class String{
	friend adventure_game::our_ostream& operator <<(adventure_game::our_ostream& stream, String output);
	friend void getline(std::istream& stream, String& stuff);
	public:
		String& operator =(std::string input);
		String& operator =(String input);
		String& operator +=(std::string input);
		String& operator +=(adventure_game::console_attribute input);
		String& operator +=(String input);
		String operator +(std::string input);
		String operator +(adventure_game::console_attribute input);
		String operator +(String input);
	private:
		std::string contents;
		std::list<int> points;
		std::list<adventure_game::console_attribute> attr;
};