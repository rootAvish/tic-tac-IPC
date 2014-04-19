/*
 this header will contain the shared memory structure and some function prototypes
 all these functions are defined in header.c , the system will automatically link these files
*/

typedef struct shared
{
    char grid[3][3] ;
    int turn ;
}shared;

//function that will display the board which we have stored in shared memory
void display(shared* data);

//function to initialize the grid with all blank spaces
void initialize(shared* data);

//function to clear the screen,yes i know how to do that
void clear();
