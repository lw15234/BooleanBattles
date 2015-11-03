# Compile with standard options
GCC = gcc -std=c99 -O3 -pedantic -Wall -Werror -o booleanBattles

# Set up the linear sequence of modules, in dependency order
BASE = booleanBattles.c base.c
ENEMY = $(BASE) enemy.c


# Make the whole program by default
default: play

# Compile and test each module
base:
	$(GCC) -DRUN=testBase $(BASE)
	./booleanBattles
enemy:
	$(GCC) -DRUN=testGrid $(ENEMY)
	./booleanBattles
