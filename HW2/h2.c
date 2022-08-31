/*****************************************
h2.c (Manhattan distance heuristic)
******************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int manhattanDistance(NODE *a_node) {
    int sum = 0;
	char c ;
	int v = 0;
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) { 
			
			if(i == 0)
             c = a_node->state->a[i+j]; 
			if(i == 1)
			 c = a_node->state->a[i+j+2]; 
			if(i == 2)
			 c = a_node->state->a[i+j+4]; 
		 
			v = c - '0';
					
            if (v != 0) { 
                int ti = (v - 1) / 3; 
                int tj = (v - 1) % 3;                 
                sum += abs(i - ti) + abs(j - tj); 
            } 
        }
    return sum;
}