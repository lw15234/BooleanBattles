# Compile with standard options
CFLAGS = `sdl2-config --cflags` -O4 -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -lm
TARGET = booleanBattles
LIBS = `sdl2-config --libs`
CC = gcc

# Set up the linear sequence of modules, in dependency order
TEST = booleanBattles.c
TESTINPUT = input.c

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
	$(CC) $(BASE) $(TEST) -DRUN=testBase -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
enemy:
	$(CC) $(ENEMY) $(TEST) -DRUN=testEnemy -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
checkAttack:
	$(CC) $(CHECKATTACK) $(TEST) -DRUN=testCheckAttack -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
damage:
	$(CC) $(DAMAGE) $(TEST) -DRUN=testDamage -o $(TARGET) $(CFLAGS) $(LIBS)
	./booleanBattles
display:
	$(CC) $(DISPLAY) $(TEST) -DRUN=testDisplay -o $(TARGET) $(CFLAGS) $(LIBS)
stateMachine:
	$(CC) $(STATEMACHINE) $(TEST) -DRUN=runStateMachine -o $(TARGET) $(CFLAGS) $(LIBS)
play:
	$(CC) $(PLAY) -o $(TARGET) $(CFLAGS) $(LIBS)


clean:
	rm -f $(TARGET)

