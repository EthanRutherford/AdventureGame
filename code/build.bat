:: This file is owned by Roger. It will compile the AdventureGame project for
:: users using Windows consoles.

:: compile the project with the ADVENTUREGAME_WIN32 symbol defined, which will compile
:: the Windows specific code
g++ *.cpp -o adventure.exe -Wall -Werror -Wextra -Wshadow -Wfatal-errors -Wno-unused-variable -pedantic-errors -DADVENTUREGAME_WIN32
