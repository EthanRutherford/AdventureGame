#############################################################################################
# Makefile for project AdventureGame - requires C++11 and the GCC C++ compiler
# Project: AdventureGame
# Owner: Roger Gee
# Commands:
# (build project:)
# $ make 
# (clean compiler output)
# $ make clean
############################################################################################

CXX = g++ -Wall -pedantic-errors -Werror -Wextra -Wshadow -Wfatal-errors -Wno-unused-variable --std=gnu++0x
CXX_obj = g++ -c -Wall -pedantic-errors -Werror -Wextra -Wshadow -Wfatal-errors -Wno-unused-variable --std=gnu++0x
OUTX = -o ../adventure
OUTOBJ = -o obj/
OBJDIR = obj
OBJFILES = $(addprefix $(OBJDIR)/,main.o custom_io.o tag.o gamemap.o people.o object.o item.o game.o creature.o game_element.o)
# use ADVENTUREGAME_WIN32 for Windows Consoles or ADVENTUREGAME_XTERM for XTerminals
MACRO = -DADVENTUREGAME_XTERM

# dependency lists...
CUSTOM_IO_H = custom_io.h
TAG_H = tag.h $(CUSTOM_IO_H)
GAME_ELEMENT_H = game_element.h $(TAG_H)
ITEM_H = item.h $(GAME_ELEMENT_H)
OBJECT_H = object.h $(ITEM_H) $(GAME_ELEMENT_H)
PEOPLE_H = people.h $(OBJECT_H) $(GAME_ELEMENT_H)
CREATURE_H = creature.h $(GAME_ELEMENT_H)
GAMEMAP_H = gamemap.h $(OBJECT_H) $(ITEM_H) $(PEOPLE_H) $(CREATURE_H) $(GAME_ELEMENT_H)
GAME_H = game.h $(GAMEMAP_H) $(GAMEMAP_H) $(PEOPLE_H) $(ITEM_H) $(CREATURE_H)

../adventure: $(OBJDIR) $(OBJFILES)
	$(CXX) $(OUTX) $(OBJFILES)


# compile each module of the project
obj/main.o: main.cpp game.h custom_io.h
	$(CXX_obj) $(OUTOBJ)main.o main.cpp $(MACRO)

obj/custom_io.o: custom_io.cpp $(CUSTOM_IO_H)
	$(CXX_obj) $(OUTOBJ)custom_io.o custom_io.cpp $(MACRO)

obj/tag.o: tag.cpp $(TAG_H)
	$(CXX_obj) $(OUTOBJ)tag.o tag.cpp $(MACRO)

obj/gamemap.o: gamemap.cpp $(GAMEMAP_H)
	$(CXX_obj) $(OUTOBJ)gamemap.o gamemap.cpp $(MACRO)

obj/people.o: people.cpp $(PEOPLE_H)
	$(CXX_obj) $(OUTOBJ)people.o people.cpp $(MACRO)

obj/object.o: object.cpp $(OBJECT_H)
	$(CXX_obj) $(OUTOBJ)object.o object.cpp $(MACRO)

obj/item.o: item.cpp $(ITEM_H)
	$(CXX_obj) $(OUTOBJ)item.o item.cpp $(MACRO)

obj/game.o: game.cpp $(GAME_H)
	$(CXX_obj) $(OUTOBJ)game.o game.cpp $(MACRO)

obj/creature.o: creature.cpp $(CREATURE_H)
	$(CXX_obj) $(OUTOBJ)creature.o creature.cpp $(MACRO)

obj/game_element.o: game_element.cpp $(GAME_ELEMENT_H)
	$(CXX_obj) $(OUTOBJ)game_element.o game_element.cpp $(MACRO)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# clean rule - delete object files and executable
clean:
	rm --verbose $(OBJDIR)/*.o ../adventure
