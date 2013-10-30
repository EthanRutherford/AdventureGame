#include "custom_io.h"
#include "game.h"
using namespace std;
using namespace adventure_game;

int main(int argc,const char* args[])
{
    if (argc > 1)
    {
        // TODO: handle command-line arguments
    }

    string name;
    exCout << "Enter the name of the markup file: ";
    getline(cin, name);
    exCout.input_event(); // inform the IO manager that the user entered input

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
