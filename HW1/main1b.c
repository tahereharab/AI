/* main1b.c */
/* runs vanilla BFS on Puzzle 8: EXAMPLE1 and EXAMPLE2 and EXAMPLE3 */ 


#include "examples.c"
#include "search.h"
#include "mark.h"


/**********************************************************************
 Plain vanilla breadth first search 
***********************************************************************/

boolean bfs_stat (char *init_configuration)
{
		STATE *init_state;
		NODE * search_tree;
		struct list_of_nodes * queue; 		/* implemented through a list of nodes, better */
		struct list_of_nodes * solution;		/* implementations exist */
		NODE * current_node;
		boolean success = FALSE;
		
		
		int expand_nodes = 0;
		int generated_nodes = 0;
		int length_queue = 0;
		int max_length_queue = 0;
		struct list_of_nodes * expand_node_list; 
		int length_expand_node_list = 0;
		


		init_state = initialize_state(init_configuration);        	/* convert the initial configuration to a state*/
		printf("\n***************************");
		printf("\n Initial configuration \n");
		print_state(init_state);
		printf("\n Hmmmmmm.....(This may take a minute)...\n");

		search_tree = initialize_search_tree(init_state);	       	/* initialize the search tree */

		/* initialize the queue */
		queue = NULL;												/* the queue is initially empty */ 
		queue=add_to_list_front(queue,search_tree);					/* we start our search with the root of search tree */

		/* do the actual search */
		while ((success == FALSE) && (queue != NULL))
		{
				current_node = first_node_in_list(queue); 			/* take the first node in the queue */
				queue = remove_first_from_list(queue);				/* and remove it from the queue */

				if (goalp(current_node)) 						 	/* Did we find a solution ? */ 
						success = TRUE;							    /* YES: bail out of the cycle */
				else
				{
					    expand_node_list = expand_node(current_node);
						queue = concatenate_lists(queue,expand_node_list);	      /* NO: expand the node and add its children to the queue */
						expand_nodes++;
						length_queue = list_length(queue);
						length_expand_node_list = list_length(expand_node_list);
						generated_nodes = generated_nodes + length_expand_node_list;
						
						if(length_queue > max_length_queue)
							max_length_queue = length_queue;
				}

				
		} 	// end while-loop

		/* solution recovery from the search tree */ 
		if (success == TRUE) 
		{
				printf("\n Solution");
				solution = generate_solution_list(current_node);				/* generate the solution path as a list of nodes */
				print_all_states_in_list(solution);					     		/* please view .c to see how this works */
				
				printf("number of expanded nodes: %ld \n", expand_nodes);
				printf("number of generated nodes: %ld \n", generated_nodes + 1);
				printf("maximum length of queue: %ld \n", max_length_queue);
				printf("number of moves: %ld \n", list_length(solution)-1);	/* output the solution */
			
		}
		else { 
				printf("\n No solution found.");
		};

		/* clean up:
		   after you are done with one search it is good to clean up so
		   that you are able to reuse the freed memory 
		 */

		printf("\n Delete solutions...");						/* delete solution list */
		delete_list(solution);
		printf("\n Delete search tree...\n");  			  		/* delete search tree structure */
		delete_search_tree(search_tree);

		return success;								   			/* tell the caller whether search was successful */
}           



/**********************************************************************
main: runs the plain bfs search on EXMAPLE1 and EXAMPLE2
 ***********************************************************************/


main()
{
		bfs_stat(EXAMPLE_1);
		printf("\n Press return to continue ... \n"); getchar();

		bfs_stat(EXAMPLE_2);
		printf("\n Press return to continue ... \n"); getchar();

		// Example 3 may take some time on a slow machine
		bfs_stat(EXAMPLE_3); 
		printf("\n Press return to continue ... \n"); getchar();
		return 0;

}

