# Compile with standard options
GCC = gcc -std=c99 -O3 -pedantic -Wall -Werror -o maze

# Set up the linear sequence of modules, in dependency order
BASE = maze.c base.c
GRID = $(BASE) grid.c
STATE = $(GRID) state.c
ENTITY = $(STATE) entity.c
ACTION = $(ENTITY) action.c
DISPLAY = $(ACTION) display.c
PLAY = $(DISPLAY) play.c

# Make the whole program by default
default: play

# Compile and test each module
base:
	$(GCC) -DRUN=testBase $(BASE)
	./maze
grid:
	$(GCC) -DRUN=testGrid $(GRID)
	./maze
state:
	$(GCC) -DRUN=testState $(STATE)
	./maze
entity:
	$(GCC) -DRUN=testEntity $(ENTITY)
	./maze
action:
	$(GCC) -DRUN=testAction $(ACTION)
	./maze
display:
	$(GCC) -DRUN=testDisplay $(DISPLAY) -lSDL2
play:
	$(GCC) -DRUN=play $(PLAY) -lSDL2

