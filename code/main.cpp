/* main.cpp
 * Project: Adventure Game
 * Owner: Everyone!
 */
#include "custom_io.h"
#include "game.h"
using namespace std;
using namespace adventure_game;

int main(int argc,const char* args[])
{
    string name;
    if (argc > 1)
        name = args[1]; // use specified file name on command-line
    else
    {
        exCout << "Please enter the name of the game file you wish to play: ";
        getline(cin,name);
        exCout.input_event();
    }

    try {
        Game game(name);
        game.run();
    }
    catch (GameException ex)
    {
        cerr << "An error occurred in " << args[0] << ": " << ex.getMessage() << endl;
        return 1;
    }

    return 0;
}
