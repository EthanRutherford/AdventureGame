#############################################################################################
# Makefile for Linux systems that run terminal emulators that support ANSI escape codes
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
OBJFILES = $(addprefix $(OBJDIR)/,test.o custom_io.o tag.o gamemap.o people.o object.o item.o game.o)
MACRO = -DADVENTUREGAME_LINUX

../adventure: $(OBJDIR) $(OBJFILES)
	$(CXX) $(OUTX) $(OBJFILES)


# compile each module of the project
# if there is one header with some serious inlining,
# then I might add it to the depedency list; normally,
# I assume that if a module's interface/implementation file(s)
# are modified, that only that module needs to be re-built
obj/test.o: test.cpp
	$(CXX_obj) $(OUTOBJ)test.o test.cpp $(MACRO)

obj/custom_io.o: custom_io.cpp custom_io.h
	$(CXX_obj) $(OUTOBJ)custom_io.o custom_io.cpp $(MACRO)

obj/tag.o: tag.cpp tag.h
	$(CXX_obj) $(OUTOBJ)tag.o tag.cpp $(MACRO)

obj/gamemap.o: gamemap.cpp gamemap.h
	$(CXX_obj) $(OUTOBJ)gamemap.o gamemap.cpp $(MACRO)

obj/people.o: people.cpp people.h
	$(CXX_obj) $(OUTOBJ)people.o people.cpp $(MACRO)

obj/object.o: object.cpp object.h
	$(CXX_obj) $(OUTOBJ)object.o object.cpp $(MACRO)

obj/item.o: item.cpp item.h
	$(CXX_obj) $(OUTOBJ)item.o item.cpp $(MACRO)

obj/game.o: game.cpp game.h
	$(CXX_obj) $(OUTOBJ)game.o game.cpp $(MACRO)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm --verbose $(OBJDIR)/*.o ../adventure
