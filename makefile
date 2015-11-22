# Compile with standard options

CFLAGS = `sdl2-config --cflags` -O4 -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm
LIBS =  `sdl2-config --libs`

GCC = gcc -o booleanBattles

# Set up the linear sequence of modules, in dependency order
BASE = base.c
ENEMY = $(BASE) enemy.c
CHECKATTACK = $(ENEMY) checkAttack.c
DAMAGE = $(CHECKATTACK) damage.c
DISPLAY = $(DAMAGE) display.c
STATEMACHINE = $(DISPLAY) stateMachine.c
PLAY = $(STATEMACHINE) play.c





# Compile and test each module
base:
	$(GCC) -DRUN=testBase $(BASE) $(CFLAGS) $(LIBS)
	./booleanBattles
enemy:
	$(GCC) -DRUN=testEnemy $(ENEMY) $(CFLAGS) $(LIBS)
	./booleanBattles
checkAttack:
	$(GCC) -DRUN=testCheckAttack $(CHECKATTACK) $(CFLAGS) $(LIBS)
	./booleanBattles
damage:
	$(GCC) -DRUN=testDamage $(DAMAGE) $(CFLAGS) $(LIBS)
	./booleanBattles
testInput:
	$(GCC) $(DISPLAY) $(CFLAGS) $(LIBS)
	./booleanBattles
stateMachine:
	$(GCC) $(STATEMACHINE) $(CFLAGS) $(LIBS)
	./booleanBattles
play:
	$(GCC) $(PLAY) $(CFLAGS) $(LIBS)
	./booleanBattles
