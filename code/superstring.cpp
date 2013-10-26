#include "superstring.h"
#include <sstream>
using namespace adventure_game;

our_ostream& operator <<(our_ostream& stream, String output)
{
	std::string word;
	word.clear();
	std::stringstream ss;
	ss.str(output.contents);
	int length = 0, num = 0;
	while (ss >> word)
	{
		length += word.length() + 1;
		if (length >= 80)
		{
			stream << "\n";
			length = 0;
		}
		if (num == output.points.front())
		{
			output.points.pop_front();
			stream << output.attr.front();
			output.attr.pop_front();
		}
		stream << word << " ";
		word.clear();
		num++;
	}
	stream << consolea_normal;
	return stream;
}

void getline(std::istream& stream, String& stuff)
{
	getline(stream, stuff.contents);
}

String& String::operator=(std::string input)
{
	contents = input;
	return *this;
}

String& String::operator=(String input)
{
	contents = input.contents;
	return *this;
}

String& String::operator+=(std::string input)
{
	contents += input;
	return *this;
}

String& String::operator +=(adventure_game::console_attribute input)
{
	std::string junk;
	std::stringstream ss;
	ss.str(contents);
	int num = 0;
	while (ss >> junk)
		num++;
	points.push_back(num);
	attr.push_back(input);
	return *this;
}

String& String::operator+=(String input)
{
	contents += input.contents;
	return *this;
}

String String::operator +(std::string input)
{
	String ans;
	ans = contents + input;
	return ans;
}

String String::operator +(adventure_game::console_attribute input)
{
	String ans = *this;
	ans += input;
	return ans;
}

String String::operator +(String input)
{
	String ans;
	ans = contents + input.contents;
	return ans;
}

