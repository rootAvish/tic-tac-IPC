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
