/* 
STUDENTS: Look in search.h for descriptions of state/list/tree manipulating functions.
Not all of the code here is of immediate interest for CS2710 students. 
 */

#include "search.h"

/* *******************************************************

STATE: problem-specific definition of state for 8-puzzle

 ****************************************************** */

/*--------------------------------------------------------------------------------*/
STATE * initialize_state(char *configuration)    	/* takes a string that encodes the state */
{						        /* and returns a new state */
		STATE * new_state;
		int pos;

		new_state = (STATE *) malloc(sizeof(STATE));
		for (int i = 0; i < 9 ; i++)
		{ 
				if (configuration[i] == '0')
				{
						pos = i;
						break;
				}
		}
		new_state->empty = pos;
		for (int i = 0; i < 9 ; i++)
				new_state->a[i] = configuration[i];
		return new_state;
}

/*--------------------------------------------------------------------------------*/
STATE *copy_state(STATE *old_state)			/* makes a copy of the state (alloc it from the free memory) */
{
		STATE *new_state;

		if (old_state == NULL) return NULL;		/* sanity check */

		new_state = (STATE *) malloc(sizeof(STATE));
		for (int i = 0; i < 9; i++)
		{
				new_state->a[i] = old_state -> a[i];
		}
		new_state->empty = old_state->empty;

		return new_state;
}

/*--------------------------------------------------------------------------------*/
void print_state(STATE *state)
{
		printf("\n------------------ \n");	
		printf("%c %c %c\n", *(state->a), *(state->a +1), *(state->a + 2));
		printf("%c %c %c\n", *(state->a + 3), *(state->a +4), *(state->a + 5));
		printf("%c %c %c\n", *(state->a + 6), *(state->a +7), *(state->a + 8));
		fflush(stdout);
}


/* compare two states (check all tiles for equality) */

boolean compare_states (STATE *state1, STATE *state2)
{
		if (strncmp(state1->a,state2->a, 9)== 0) return TRUE;
		else return FALSE;
}

/*  **********************************
	;; APPLICATION OF OPERATORS

STUDENTS: make sure you understand this and the apply_operator function

 ********************************** */

/* 
Recall: 
UP_MOVE = 0, DOWN_MOVE=1, LEFT_MOVE=2, RIGHT_MOVE=3
const int NO_MOVE = -1;
 */

/* table of valid moves of the empty tile */
static int valid_moves[9][4]=
{
		{NO_MOVE,3,NO_MOVE,1},
		{NO_MOVE,4,0,2},
		{NO_MOVE,5,1,NO_MOVE},
		{0,6,NO_MOVE,4},
		{1,7,3,5},
		{2,8,4,NO_MOVE},
		{3,NO_MOVE,NO_MOVE,7},
		{4,NO_MOVE,6,8},
		{5,NO_MOVE,7,-1}
};


/* *******************************************
   apply_operator function

   - takes a state and applies an operator to it 
   - if the move is valid it returns a new state (allocated in the free memory)
   if not return NULL
 ************************************* */

/*--------------------------------------------------------------------------------*/
STATE * apply_operator(STATE *old_state, int oper)
{
		STATE *new_state;
		int pos;

		if (old_state == NULL) return NULL;                     /* sanity check */

		if (valid_moves[old_state->empty][oper]== NO_MOVE)
				return NULL;
		else
		{
				new_state=copy_state(old_state);
				pos=valid_moves[old_state->empty][oper];
				new_state->a[old_state->empty]=old_state->a[pos];
				new_state->a[pos]='0';
				new_state->empty=pos;
		}
		return new_state;
}

/* *****************************************************
   ;;   SEARCH TREE / NODE

STUDENTS: this is important

 ****************************************************** */

/*--------------------------------------------------------------------------------*/
/* search tree functions */
NODE *initialize_search_tree(STATE *init_state)
{
		NODE *root;

		root = (NODE *)malloc(sizeof(NODE));
		root->state=init_state;
		root->parent = NULL;
		root->op = -1;
		root->children = NULL;
		root->g_value=0;
		return root;
}


/*--------------------------------------------------------------------------------*/
/* node expansion:
   - generates a new set of children states from the current node's state
   - creates nodes for them and adds them to the search tree
   - returns a new set of nodes in the list structure
   (if no new nodes can be generated it returns NULL = empty list) */

struct list_of_nodes *expand_node(NODE *a_node)
{
		int op;
		STATE *new_state;
		NODE *new_node;
		struct list_of_nodes *new_nodes_list=NULL;


		for (op=3;op>=0; op--) /* loop through all possible empty-tile operators */
		{
				new_state =apply_operator(a_node->state, op);
				if (new_state !=NULL)
				{
						/*a new valid state*/
						/*create node for a newly generated state */
						new_node = (NODE *)malloc(sizeof(NODE));
						new_node->state= new_state;
						new_node->parent=a_node;
						new_node->op= op;
						new_node->g_value =a_node->g_value + 1;
						new_node->children=NULL;

						/* now put the new node in the list of newly generated nodes */
						new_nodes_list = add_to_list_front(new_nodes_list, new_node);
				}
		}
		/* update children attribute of the a_node */
		a_node->children=new_nodes_list;
		/* return the copy of the new_nodes list */
		return copy_list(new_nodes_list);
}

/*--------------------------------------------------------------------------------*/
/* checks for the goal state */
int goalp(NODE *curr_node)
{
		if (strncmp(curr_node->state->a,"123456780", 9)== 0)
				return TRUE;
		else
				return FALSE;
}

/*--------------------------------------------------------------------------------*/
/* creates a list of nodes that contain the solution */
struct list_of_nodes *generate_solution_list(NODE *goal_node)
{
		struct list_of_nodes* solution_path=NULL;
		NODE *node_pointer;

		node_pointer=goal_node;
		solution_path = add_to_list_front(solution_path, node_pointer);
		while (node_pointer->parent != NULL)
		{
				node_pointer=node_pointer->parent;
				solution_path = add_to_list_front(solution_path, node_pointer);
		}
		return solution_path;
}

/*--------------------------------------------------------------------------------*/
/* checks the node of the search tree for cyclic repeats */
boolean check_cyclic_repeats(NODE *curr_node)
{
		/* STUDENTS: please modify this function to check for cyclic repeats */
		NODE *node_pointer;
		node_pointer=curr_node;
		while (node_pointer->parent != NULL)
		{
				node_pointer=node_pointer->parent;
				if (compare_states(curr_node->state , node_pointer->state ) == TRUE)
					return TRUE;
					
		}
		return FALSE;
}


/*--------------------------------------------------------------------------------*/
/****** delete tree routines ****/
void delete_search_tree_list(struct list_of_nodes *node_list)
{
		if (node_list != NULL)
		{
				delete_search_tree_list(node_list->next);
				delete_search_tree(node_list->item);
				free(node_list);
		}
		return;
}

/*--------------------------------------------------------------------------------*/
void delete_search_tree(NODE *search_tree_node)
{
		if (search_tree_node != NULL)
		{
				delete_search_tree_list(search_tree_node->children);
				free(search_tree_node);
		}
		return;
}


/* ************************************************

   ;;  List processing functions for the list_of_nodes structure

STUDENTS: just use it as described in search.h

 ************************************************ */


/*--------------------------------------------------------------------------------*/
/** addition of an element to the front of the list ***/
struct list_of_nodes * add_to_list_front(struct list_of_nodes * old_list, 
				NODE * new_node)
{
		struct list_of_nodes * new_list_cell;

		new_list_cell = (struct list_of_nodes *)malloc(sizeof(struct list_of_nodes));
		new_list_cell->item = new_node;
		new_list_cell->next=old_list;
		return new_list_cell;  
}

/*--------------------------------------------------------------------------------*/
/** addition of an element to the rear of the list ***/
struct list_of_nodes * add_to_list_rear(struct list_of_nodes * old_list, 
				NODE * new_node)
{
		struct list_of_nodes * new_list_cell;
		struct list_of_nodes * search_pointer;

		new_list_cell = (struct list_of_nodes *)malloc(sizeof(struct list_of_nodes));
		new_list_cell->item = new_node;
		new_list_cell->next=NULL; /* end of the list thus must be NULL*/

		/* find the last list cell in the old_list*/
		if (old_list == NULL)
				old_list=new_list_cell;
		else
		{
				search_pointer=old_list;
				while (search_pointer->next != NULL)
						search_pointer=search_pointer->next;
				search_pointer->next = new_list_cell;
		}
		return old_list;  
}

/*--------------------------------------------------------------------------------*/
/** access the first element of the list ***/
NODE * first_node_in_list(struct list_of_nodes * a_list)
{
		if (a_list == NULL)
				return NULL;
		else return a_list->item;
}

/*--------------------------------------------------------------------------------*/
/* takes the list and removes the first element from it */
struct list_of_nodes * remove_first_from_list(struct list_of_nodes * a_list)
{
		struct list_of_nodes * modified_list;

		if (a_list == NULL)
				return NULL;
		else 
		{
				modified_list=a_list->next;
				free(a_list);
				return(modified_list);
		}
}

/*--------------------------------------------------------------------------------*/
/*** makes a copy of a list (its top list structure) to make it safe 
  for some operation, e.g. to concatenation **/
struct list_of_nodes * copy_list (struct list_of_nodes * a_list)
{
		struct list_of_nodes * search_pointer;
		struct list_of_nodes * track_pointer;
		struct list_of_nodes * new_list;
		struct list_of_nodes * new_list_cell;

		if (a_list == NULL)
				return NULL;

		search_pointer = a_list;
		new_list_cell = (struct list_of_nodes *)malloc(sizeof(struct list_of_nodes));
		new_list = new_list_cell;
		new_list->item = search_pointer->item;
		track_pointer=new_list;

		while (search_pointer->next != NULL)
		{
				search_pointer=search_pointer->next;
				new_list_cell = (struct list_of_nodes *)malloc(sizeof(struct list_of_nodes));
				new_list_cell->item=search_pointer->item;
				track_pointer->next=new_list_cell;
				track_pointer=new_list_cell;
		}

		new_list_cell->next=NULL; 

		return new_list;
}

/*--------------------------------------------------------------------------------*/
/*** deletes a list skelet of the list, items inside are not deleted **/
void delete_list (struct list_of_nodes * a_list)
{
		if (a_list != NULL)
		{
				delete_list(a_list->next);
				free(a_list);
		}
		return;
}

/*--------------------------------------------------------------------------------*/
/** concatenates two lists into one list (destructive operation) **/
struct list_of_nodes * concatenate_lists (struct list_of_nodes * a_list1, 
				struct list_of_nodes * a_list2)
{
		struct list_of_nodes * search_pointer;
		if (a_list1 == NULL)
				return a_list2;
		else
		{
				search_pointer=a_list1;
				while (search_pointer->next != NULL)
						search_pointer=search_pointer->next;
				search_pointer->next = a_list2;
				return a_list1;
		}
}

/*--------------------------------------------------------------------------------*/
int list_length(struct list_of_nodes * a_list)
{
		if (a_list == NULL)
				return 0;
		else
				return (1+list_length(a_list->next));
}

/*--------------------------------------------------------------------------------*/
/* prints states in the list of nodes */
void print_all_states_in_list(struct list_of_nodes * a_list)
{
		struct list_of_nodes *search_pointer;

		search_pointer =a_list;
		printf("\n=================================");
		// printf("%\n Printing list of nodes"); 
		if (a_list != NULL)
		{
				do 
				{ 
						print_state(search_pointer->item->state);  
						search_pointer=search_pointer->next;
				}
				while (search_pointer != NULL);
		}
		printf("\n=================================\n ");
}





