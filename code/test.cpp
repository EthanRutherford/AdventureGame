// not meant to be included in final build
#include "custom_io.h"
#include "gamemap.h"
using namespace std;
using namespace adventure_game;

int main()
{
    gamemap theMap("markup.txt");
    theMap.print();
    exCout << "Current room message:\n";
    if ( theMap.is_valid_current_room() )
        theMap.get_current_room()->look();
}
