:: This file is owned by Roger. It will compile the AdventureGame project for
:: users using Windows console (Command Prompt)

:: compile the project with the ADVENTUREGAME_WIN32 symbol defined
g++ *.cpp -o adventure.exe -Wall -Werror -Wextra -Wshadow -Wfatal-errors -Wno-unused-variable -pedantic-errors -DADVENTUREGAME_WIN32
