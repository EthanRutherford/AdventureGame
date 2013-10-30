#include "custom_io.h"
#include "game.h"
using namespace std;
using namespace adventure_game;

int main()
{
    string name;
	cout << "Enter the name of the markup file: ";
	getline(cin, name);
	Game game(name);
    game.run();
}
