# Compile with standard options
GCC = gcc `sdl2-config --cflags` -std=c99 -O3 -pedantic -Wall -Werror -o booleanBattles -lm `sdl2-config --libs`

# Set up the linear sequence of modules, in dependency order
TEST = booleanBattles.c
BASE = base.c
ENEMY = $(BASE) enemy.c
CHECKATTACK = $(ENEMY) checkAttack.c
DAMAGE = $(CHECKATTACK) damage.c
DISPLAY = $(DAMAGE) display.c
STATEMACHINE = $(DISPLAY) stateMachine.c
PLAY = $(STATEMACHINE) play.c


# Make the whole program by default
default: play

# Compile and test each module
base:
	$(GCC) -DRUN=testBase $(BASE) $(TEST)
	./booleanBattles
enemy:
	$(GCC) -DRUN=testEnemy $(ENEMY) $(TEST)
	./booleanBattles
checkAttack:
	$(GCC) -DRUN=testCheckAttack $(CHECKATTACK) $(TEST)
	./booleanBattles
damage:
	$(GCC) -DRUN=testDamage $(DAMAGE) $(TEST)
	./booleanBattles
display:
	$(GCC) -DRUN=testDisplay $(DISPLAY) $(TEST)
	./booleanBattles
stateMachine:
	$(GCC) -DRUN=runStateMachine $(STATEMACHINE)
	./booleanBattles
play:
	$(GCC) $(STATEMACHINE)
	./booleanBattles
