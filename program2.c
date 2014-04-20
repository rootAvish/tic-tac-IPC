/*
    This program controls movement(s) for player 2
    program1 should be run first
*/
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h>
#include <sys/shm.h>

int main(void)
{
    int shmid = shmget((key_t)1234,sizeof(shared),IPC_CREAT  | 0666);
    int i=0,j=0;
    int posx,posy,choice,legal;
    
    if ( shmid == -1 )
    {
        fprintf(stderr,"shared memory could not be created!,program will now abort\n");
        exit(EXIT_FAILURE);
    }
    shared* data = (shared*)shmat(shmid,NULL,0);
    
    if ( data == NULL )
    {
        fprintf(stderr,"shared memory could not be attached!,program will now abort\n");
        exit(EXIT_FAILURE);
    }
    
    clear();
    
    //currently the program loops over infinitely
    while ( 1 )
    {
        while ( data->turn == 1 )   {
            printf("Player 1 is moving,please wait.......\n");
            sleep(2);
        }
            
        display(data);
        legal=0;
        
        //player2 will now move     
        while ( !legal )
        {
            printf("Choose where to place mark : ");
            scanf("%d",&choice);
            
            posx = --choice/3;
		    posy = choice%3;
            
            if ( data->grid[posx][posy] != 'x' && 
                 data->grid[posx][posy] != 'o' )
            {
                data->grid[posx][posy] = 'o' ;
                legal=1;
            }
            else
                printf("Wrong move,please retry!\n");
         }
        //player2 has moved
        
        display(data);
        data->turn = 1;
    }
    
    //detaching the shared memory
    if ( shmdt(data) != 0)
    {
        fprintf(stderr,"shared memory could not be detached!,program will now abort\n");
        exit(EXIT_FAILURE);   
    }
    return 0;
}
