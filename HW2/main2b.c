/* main2b.c */

/* defines:
   - the evaluation function based search
   - uniform cost search within the framework
   - runs the search on Puzzle 8: EXAMPLE1, EXAMPLE2 and EXAMPLE3 

 */ 


#include "examples.c"
#include "search.h"
#include "mark.h"
#include "pqueue.h"


/**********************************************************************
  Uniform cost search 
 ***********************************************************************/


/** ****************************************************************
  define evaluation and heuristic functions
 *******************************************************************/


int h_function(NODE *a_node)
{
		return 0;
}

int f_function(NODE *a_node)
{
		return a_node->g_value;
}


/**********************************************************************
  Evaluation-function (f-function) based search 
 ***********************************************************************/

boolean f_search (char *init_configuration)
{
		STATE *init_state;
		NODE * search_tree;
		struct list_of_nodes * queue=NULL; 		      /* implemented as a list of nodes */ 
		struct list_of_nodes * solution;
		struct list_of_nodes * new_nodes;
		NODE * current_node;
		boolean success = FALSE;

		//vars for collecting statistics
		long int nodes_expanded=0;
		long int nodes_generated=0;
		long int length_queue=0;
		long int max_queue=0;

		// auxiliary vars
		int no_of_new_nodes=0;


		init_state = initialize_state(init_configuration);     /* convert the initial configuration to a state*/
		printf("\n***************************");
		printf("\n Initial configuration \n");
		print_state(init_state);

		search_tree = initialize_search_tree(init_state);     /* initialize the search tree */
		initialize_mark_structure();

		queue = NULL; 
		queue = add_to_list_front(queue,search_tree);
		length_queue++;    //incrementing since we added the root to the queue

		while ((success == FALSE) &&  (queue != NULL))
		{
				current_node = first_node_in_list(queue);                              /* take the first node in the queue */
				queue = remove_first_from_list(queue);                                 /* and remove it from the queue */
				length_queue--;                                                       //decrese the length of the queue by 1

				if (goalp(current_node))		/* Did we find a solution ? */
						success=TRUE;		       /* YES: bail out of the cycle */
				else
				{
					if(check_mark(current_node) == FALSE)
						{
						new_nodes = expand_node(current_node);  // expand the node - updates g_value, h_value and f_value of the node
						nodes_expanded++;                         //update the statistics
						mark_node(current_node);
						no_of_new_nodes=list_length(new_nodes);
						nodes_generated = nodes_generated + no_of_new_nodes;
						length_queue = length_queue + no_of_new_nodes;
						if (length_queue > max_queue) max_queue = length_queue;
						queue = add_to_priority_queue (queue,new_nodes);    /** add children of the expanded node to the queue */
						}
				}

		}

		if (success == TRUE) 
		{
				solution = generate_solution_list(current_node);			 /* generate the solution path as a list of nodes */
				print_all_states_in_list(solution);					 /* and output the solution */
				printf("\n Solution-length: %d \n", list_length(solution)-1);
				printf("\n Number of nodes expanded: %ld \n", nodes_expanded);
				printf("\n Number of nodes generated: %ld \n", nodes_generated);
				printf("\n Maximum size of the queue: %ld \n", max_queue);
		}

		/* clean up */

		delete_search_tree(search_tree);

		delete_list(solution);
		delete_marks();

		return success;

}           


/**********************************************************************
main: runs the f_value search to perform the uniform cost search
 ***********************************************************************/


int main()
{
		f_search (EXAMPLE_1);
		printf("\n Press return to continue ... \n"); getchar();

		f_search (EXAMPLE_2);
		printf("\n Press return to continue ... \n"); getchar();
		// do not forget to run EXAMPLE_3 for other parts of the assignment
		f_search (EXAMPLE_3); 

		return 0;

}

