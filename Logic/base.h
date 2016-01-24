/*Contains basic test functions and forward declarations to use throughout
the rest of the game*/

#define QUIT -2

/*Print a success message*/
void succeed(char *message);

/*Print an error message and exit*/
void fail(char *message);

/*Forward reference so other modules can change state of game
    (used mainly in stateMachine)*/
typedef enum battleState{
    START,
    PLAYERINPUT,
    PLAYERACTION,
    WIN,
    LOSE
} battleState;
