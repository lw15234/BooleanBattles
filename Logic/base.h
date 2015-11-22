// Reports a test success
void succeed(char *message);

// Report a test failure or bug, and stop the program.
void fail(char *message);


typedef enum battleState{
    START,
    PLAYERINPUT,
    PLAYERACTION,
    WIN,
    LOSE
} battleState;

