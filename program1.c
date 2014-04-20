/*
    this program controls movement for player 1
    also decides who moves first and ergo,should be the first program to execute
*/
#include <stdio.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"
#include <time.h>

int main(void)
{
    int shmid = shmget((key_t)4321,sizeof(shared),IPC_CREAT | 0666);
    int msqid;
    int i=0,j=0;
    int posx,posy,choice;
    long int msgtr=0;
 
    srand(time(NULL));   
    if ( shmid == -1 )
    {
        fprintf(stderr,"Shared Memory could not be created, Program will now abort!\n");
        exit(EXIT_FAILURE);
    }

    msqid = msgget((key_t)4321, 0666|IPC_CREAT);
	if(msqid == -1){
		printf("Message Queue attachment failed, Program will now abort!");
	}
    shared* data = (shared*)shmat(shmid,NULL,SHM_RND);
    
    if ( data == NULL )
    {
        fprintf(stderr,"Shared Memory could not be attached, Program will now abort!\n");
        exit(EXIT_FAILURE);
    }
    clear();
    initialize(data);
     
    if ( rand() % 2 == 0 )  {
        data->turn=1;
        printf("Player1 goes first,sign for player 1 is 'x'\n");
    }
    else    {
    
        data->turn=2;
        printf("Player2 goes first,sign for player 2 is 'o'\n");
    }
    
	while (1)
	{
		while (data->turn == 2)   {
			printf("Player 2 is moving,please wait.....\n");
			//sleep(2);
            //Message being received via message queue!
            if (msgrcv(msqid, (void *)data, 1024, msgtr, 0) == -1){
                printf("Message not received. Trying Again!");
            }   
            else{
				//printf("Received Message : %d,%d",data->move,data->count);
				data->turn = 1;
			}
		}
		display(data);
		if (!check(data))
		{
			//player1 moves  
			if (data->count > 8)
			{
				printf("\n%sIts a Tie !!%s\n",YEL,NRM);
				break;
			}
			else
			{
				do
				{
					printf("Choose where to place mark : ");
					scanf("%d", &choice);
					data->move=choice;
					msgtr = 0; 
				
					posx = --choice / 3;
					posy = choice % 3;
				} while (choice<0 || choice> 9 || data->grid[posx][posy] > '9');
				data->grid[posx][posy] = 'x';
				data->count = data->count + 1;
				
				//Message being sent by message Queue!
				if (msgsnd(msqid, (void *)data, 1024, 0) == -1){
					printf("Failed to send message. Please Try again!");
				}
				
				if (data->count > 8 && !check(data))
                {
                    display(data);
                    printf("\n%sIts a Tie!!%s\n",YEL,NRM);
                    break;
                }
                
                
				//player 1 has moved

				display(data);
			
				data->turn = 2;
				
				if ( check(data) )  {
                    printf("%sCongratulations!,you have won the game!%s\n",GRN,NRM);
                    break;
                }
                
			}
		}
		else
		{
			printf("\n%sPlayer 2 is the Winner of the game!%s\n",GRN,NRM);
			data->turn = 2;
			break;
		}
		
		
	}
     //detaching the shared memory
    if ( shmdt(data) != 0)
    {
        fprintf(stderr,"shared memory could not be detached!,program will now abort\n");
        exit(EXIT_FAILURE);   
    }
    return 0;
}
