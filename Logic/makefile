# Compile with standard options
CFLAGS = `sdl2-config --cflags` -O4 -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm
TARGET = booleanBattles
LIBS = `sdl2-config --libs`
CC = gcc

# Set up the linear sequence of modules, in dependency order
TESTRUN = testRun.c
TESTINPUT = testInput.c

BASE = base.c
ENEMY = $(BASE) enemy.c
CHECKATTACK = $(ENEMY) checkAttack.c
DAMAGE = $(CHECKATTACK) damage.c
BASEDISPLAY = $(DAMAGE) baseDisplay.c
ENTITY = $(BASEDISPLAY) entity.c
DISPLAYBUTTONS = $(ENTITY) displayButtons.c
ATTACKANIMATION = $(DISPLAYBUTTONS) attackAnimation.c
STATEMACHINE = $(ATTACKANIMATION) stateMachine.c
PLAY = $(STATEMACHINE) play.c



# Make the whole program by default
default: play

# Compile and test each module
base:
	$(CC) $(BASE) $(TESTRUN) -DRUN=testBase -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
enemy:
	$(CC) $(ENEMY) $(TESTRUN) -DRUN=testEnemy -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
checkAttack:
	$(CC) $(CHECKATTACK) $(TESTRUN) -DRUN=testCheckAttack -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
damage:
	$(CC) $(DAMAGE) $(TESTRUN) -DRUN=testDamage -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
baseDisplay:
	$(CC) $(BASEDISPLAY) $(TESTRUN) -DRUN=testBaseDisplay -o $(TARGET) $(CFLAGS) $(LIBS)
entity:
	$(CC) $(ENTITY) $(TESTRUN) -DRUN=testEntity -o $(TARGET) $(CFLAGS) $(LIBS)
displayButtons:
	$(CC) $(DISPLAYBUTTONS) $(TESTRUN) -DRUN=testDisplayButtons -o $(TARGET) $(CFLAGS) $(LIBS)
attackAnimation:
	$(CC) $(ATTACKANIMATION) $(TESTRUN) -DRUN=testAttackAnimation -o $(TARGET) $(CFLAGS) $(LIBS)
stateMachine:
	$(CC) $(STATEMACHINE) $(TESTRUN) -DRUN=testStateMachine -o $(TARGET) $(CFLAGS) $(LIBS)
play:
	$(CC) $(PLAY) -o $(TARGET) $(CFLAGS) $(LIBS)


clean:
	rm -f $(TARGET)

