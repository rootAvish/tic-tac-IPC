/*
This program controls movement(s) for player 2
program1 should be run first
*/
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>

int main(void)
{
    int shmid = shmget((key_t)4321,sizeof(shared),IPC_CREAT | 0666);
    int msqid;
    int i=0,j=0;
    int posx,posy,choice;
    long int msgtr=0;
    
    if ( shmid == -1 )
    {
        fprintf(stderr,"Shared Memory could not be created, Program will now abort!\n");
        exit(EXIT_FAILURE);
    }

    msqid = msgget((key_t)4321, 0666|IPC_CREAT);
    if(msqid == -1){
        printf("Message Queue attachment failed, Program will now abort!");
    }
    shared* data = (shared*)shmat(shmid,NULL,0);
    
    if ( data == NULL )
    {
        fprintf(stderr,"Shared Memory could not be attached, Program will now abort!\n");
        exit(EXIT_FAILURE);
    }
    
    clear();
    
    //the program loops over infinitely
    while ( 1 )
    {
        while ( data->turn == 1 ) {
            printf("Player 1 is moving,please wait.......\n");
            //sleep(2);
            //Message being received via Message Queue!
            if (msgrcv(msqid, (void *)data, 1024, msgtr, 0) == -1){
                printf("Message not received. Trying Again!");
            }
            else{
                //printf("Received Message : %d,%d",data->move,data->count);
                data->turn = 2;
            }
        }
        display(data);
        if (!check(data))
        {
        //player2 will now move
            if (data->count > 8)
            {
                printf("\n%sIt's a Tie!!%s\n",YEL,NRM);
                break;
            }
            else
            {
                do
                {
                    printf("Choose where to place mark : ");
                    scanf("%d", &choice);

                    posx = --choice / 3;
                    posy = choice % 3;
                } while (choice<0 || choice>9 || data->grid[posx][posy] >'9');
                data->grid[posx][posy] = 'o';
                 data->count = data->count + 1;
                
                //Message being sent by message Queue!
                    data->move = choice;
                    if (msgsnd(msqid, (void *)data, 1024, 0) == -1){
                        printf("Failed to send message. Please Try again!");
                    }
				if (data->count > 8 && !check(data))
                {
                    display(data);
                    printf("\n%sIt's a Tie!!%s\n",YEL,NRM);
                    break;
                }

                   //player2 has moved
                display(data);
                                
               
                data->turn = 1;
                
                if ( check(data) )  {
                    printf("%sCongratulations!,you have won the game!%s\n",GRN,NRM);
                    break;
                }
               
            }
        }
        else
        {
            printf("\n%sPlayer 1 is the Winner of the game!%s\n",GRN,NRM);
            data->turn = 1;
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
