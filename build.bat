:: Build script for Windows systems
:: Project: AdventureGame
:: Owner: Roger Gee

g++ -o  adventure.exe code\*.cpp -DADVENTUREGAME_WIN32 -Wall -pedantic-errors -Werror -Wextra -Wshadow -Wfatal-errors -Wno-unused-variable
