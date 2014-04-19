#include <stdio.h>
#include "header.h"

void display(shared * data)
{
    int i,j;
    
    for ( i=0 ; i < 3 ; i++ )
    {
        for ( j=0 ; j < 3 ; j++ )
        {
            printf("%d ",data->grid[i][j]);
        }
    }
}
