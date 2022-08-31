#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/* ********************************************************* */
/* DIGIT structure */
/* input (x):  - bias stored in x[0], always set to 1 !!!
               - digit stored in x[1],..x[64] */
/* output (y): either 0 or 1 */ 
typedef struct
{
        double x[65];   
        double y; /* if digit, test=0, if test_digit test=1*/
}DIGIT;


/* ******************************************************* */
/* definitions of training and testing data sets */

/* sizes */
#define NUM_TEST_DIGS 400

#define NUM_TRAIN_DIGS 100

typedef enum {TRAINING_DIGIT=0, TESTING_DIGIT=1} FLAG;

DIGIT testing_set[NUM_TEST_DIGS];
DIGIT training_set[NUM_TRAIN_DIGS];


/* ****************************************************** */
/* weights for the logistic regression model
can be represented as an array of 65 doubles:
      w_0 - bias weight 
      w[1],.. w[64] - weights for digit inputs */
/* note that indexes for x and w vectors match */

double weights_opt[65];

