#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int main(void)
{
    int shmid = shmget((key_t)1234,sizeof(shared),IPC_CREAT | 0666);
    int i=0,j=0;
    
    if ( shmid == -1 )
    {
        fprintf(stderr,"shared memory could not be created!,program will now abort\n");
        exit(EXIT_FAILURE);
    }
    shared* data = (shared*)shmat(shmid,NULL,SHM_RND);
    
    if ( data == NULL )
    {
        fprintf(stderr,"shared memory could not be attached!,program will now abort\n");
        exit(EXIT_FAILURE);
    }
   
/*    if ( rand() % 2 == 0 )
        data->turn=1;
    else
        data->turn=2; */
        
    data->turn = 1;
    while ( 1 )
    {
        while ( data->turn == 2 )
            ;
            
        data->grid[0][0] = getchar() ; 
        
        data->turn = 2; 
    }
    if ( shmdt(data) != 0)
    {
        fprintf(stderr,"shared memory could not be detached!,program will now abort\n");
        exit(EXIT_FAILURE);   
    }
    return 0;
}
