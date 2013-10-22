// not meant to be included in final build
#include "custom_io.h"
using namespace std;
using namespace adventure_game;

int main()
{
    exCout.clear_screen();
    exCout << "This program counts the number of symbols found in an input string.\n";

    string input;
    exCout << "Enter a line:\n";
    getline(cin,input);

    char ch;
    exCout << "Enter a search symbol: ";
    ch = cin.get();

    int times = 0;
    for (size_t i = 0;i<input.length();i++)
	if (input[i] == ch)
	    exCout << consolea_fore_blue << ch << consolea_normal, times++;
	else
	    exCout.put( input[i] );

    exCout << consolea_normal << "\nFound the symbol " << times << " times.\n";
}
