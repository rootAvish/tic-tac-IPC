#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int main(void)
{
    int shmid = shmget((key_t)1234,sizeof(shared),IPC_CREAT | 0666);
    int i=0,j=0;
    int posx,posy,choice;
    
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
    clear();
    initialize(data);
     
    if ( rand() % 2 == 0 )
        data->turn=1;
    else
        data->turn=2;
        
    data->turn = 1;
    
    while ( 1 )
    {
        while ( data->turn == 2 )   {
            printf("Player 2 is moving,plese wait.....\n");
            sleep(2);
        }
        
        display(data);
            
        printf("Choose where to place mark : ");
        scanf("%d",&choice);
        
        posx = --choice/3;
		posy = choice%3;
        
        data->grid[posx][posy] = 'x' ;
        
        display(data);
        data->turn = 2; 
    }
    
    if ( shmdt(data) != 0)
    {
        fprintf(stderr,"shared memory could not be detached!,program will now abort\n");
        exit(EXIT_FAILURE);   
    }
    return 0;
}
