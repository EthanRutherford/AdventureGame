# Adventure Game Project - CS 230

## Members:
	Ethan R.
	Ethan W.
	Roger G.

## Links from Canvas:
[Wikipedia Article](http://en.wikipedia.org/wiki/Colossal_Cave_Adventure)

[Fan Page](http://www.rickadams.org/adventure/)

[Spoiler Hints](http://www.rickadams.org/adventure/d_hints/index.html">Spoiler Hints)

## Division of Labor:
List tasks for each member of the group. Feel free to make changes. I may have forgotten which ones went with whom...
* Ethan R.
	1. objects
	2. player
	3. 
* Ethan W.
	1. items
	2. creatures
	3. 
* Roger G.
	1. markup system for adventure text file
	2. room class design
	3. io system design
		* I'll use conditional compilation to do terminal/console buffering/coloring (Ethan: actually, if
		we follow the game's original design there is no menu rendering or screen clearing. We can continue
		this idea if you want though.)
		* libraries:
			* Linux: curses/ANSI color codes
			* Windows: win32 api console objects