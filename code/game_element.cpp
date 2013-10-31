/* game_element.cpp
 * Project: Adventure Game
 * Owner: Roger Gee
 */
#include "game_element.h"
using namespace std;
using namespace adventure_game;

bool game_element::compare_name(const string& elementName) const
{
    string lowerName = name, lowerElem = elementName;
    for (size_t i = 0;i<lowerName.length();i++)
        if (lowerName[i]>='A' && lowerName[i]<='Z')
            lowerName[i] -= 'A', lowerName[i] += 'a';
    for (size_t i = 0;i<lowerElem.length();i++)
        if (lowerElem[i]>='A' && lowerElem[i]<='Z')
            lowerElem[i] -= 'A', lowerElem[i] += 'a';
    return lowerElem == lowerName;
}
