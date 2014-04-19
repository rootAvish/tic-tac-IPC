#include <stdio.h>
#include "header.h"

void display(shared * data)
{
    printf("\n\n");
	printf(" %c | %c | %c\n", data->grid[0][0], data->grid[0][1], data->grid[0][2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c\n", data->grid[1][0], data->grid[1][1], data->grid[1][2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c\n", data->grid[2][0], data->grid[2][1], data->grid[2][2]);
}

void initialize(shared* data)
{
    int i=0,j=0;
    
    for ( i=0 ; i < 3 ; i++ )
    {
        for ( j=0 ; j < 3 ; j++ )
        {
            data->grid[i][j] = ' ';
        }
    }
}

void clear()
{
    printf("\e[1;1H\e[2J");
}

