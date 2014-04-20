/*
this header will contain the shared memory structure and some function prototypes
all these functions are defined in header.c , the system will automatically link these files
*/
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define BLU  "\x1B[34m"

typedef struct shared
{
    char grid[3][3] ;
    int turn ;
    int msgtype;
	int count;	// counts the no. of turns
	int move;
}shared;

//function that will display the board which we have stored in shared memory
void display(shared* data);

//function to initialize the grid with all blank spaces
void initialize(shared* data);

//function to check the winning condition , return 1 for success and 0 for failure
int check(shared* data);
//function to clear the screen,yes i know how to do that
void clear();
