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
ATTACKANIMATION = $(DAMAGE) attackAnimation.c
DISPLAY = $(ATTACKANIMATION) display.c
STATEMACHINE = $(DISPLAY) stateMachine.c
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
attackAnimation:
	$(CC) $(ATTACKANIMATION) -o $(TARGET) $(CFLAGS) $(LIBS)
display:
	$(CC) $(DISPLAY) $(TESTRUN) -DRUN=testDisplay -o $(TARGET) $(CFLAGS) $(LIBS)
stateMachine:
	$(CC) $(STATEMACHINE) $(TESTRUN) -DRUN=runStateMachine -o $(TARGET) $(CFLAGS) $(LIBS)
play:
	$(CC) $(PLAY) -o $(TARGET) $(CFLAGS) $(LIBS)


clean:
	rm -f $(TARGET)

