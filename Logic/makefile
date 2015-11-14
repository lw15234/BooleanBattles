# Compile with standard options
GCC = gcc -std=c99 -O3 -pedantic -Wall -Werror -o booleanBattles

# Set up the linear sequence of modules, in dependency order
BASE = booleanBattles.c base.c
ENEMY = $(BASE) enemy.c
CHECKATTACK = $(ENEMY) checkAttack.c
DAMAGE = $(CHECKATTACK) damage.c
TESTINPUT = $(DAMAGE) testInput.c
STATEMACHINE = $(TESTINPUT) stateMachine.c


# Make the whole program by default
default: play

# Compile and test each module
base:
	$(GCC) -DRUN=testBase $(BASE)
	./booleanBattles
enemy:
	$(GCC) -DRUN=testEnemy $(ENEMY)
	./booleanBattles
checkAttack:
	$(GCC) -DRUN=testCheckAttack $(CHECKATTACK)
	./booleanBattles
damage:
	$(GCC) -DRUN=testDamage $(DAMAGE)
	./booleanBattles
testInput:
	$(GCC) -DRUN=testInput $(TESTINPUT)
	./booleanBattles
stateMachine:
	$(GCC) -DRUN=runStateMachine $(STATEMACHINE)
	./booleanBattles
