#include "game_element.h"
using namespace std;
using namespace adventure_game;

bool game_element::compare_name(const string& elementName) const
{
    string lowerName = name;
    for (size_t i = 0;i<lowerName.length();i++)
        if (lowerName[i]>='A' && lowerName[i]<='Z')
            lowerName[i] -= 'A', lowerName[i] += 'a';
    return elementName == lowerName;
}
