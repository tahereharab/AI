#include "main11.h"

void print_digit(DIGIT);

void read_digit(FLAG flag)	/* Loads the training set if you use the TRAINING_DIGIT flag */
{							/* Loads the testing set if the TESTING_DIGIT flag is used */
	FILE *fptr; 
	FILE *mptr;
	char c[2];
	int counter = 0;
	int digit_counter = 0;
	if(flag == TRAINING_DIGIT)
		digit_counter = 100;	
	else
		digit_counter = 400;	

	if(flag == TRAINING_DIGIT) /*training digits*/
	{
		fptr = fopen("digit_x.dat", "r");
	}
	else
		fptr = fopen("digit_x_test.dat", "r");

	if( fptr == NULL)
	{
		fprintf(stderr, "Error: The file could not be opened \n");
	}

	while(counter != digit_counter)
	{
		/*no error check so better make sure that your file is not jinxed*/
		if(flag == TRAINING_DIGIT)
			for(int i = 1; i < 65; i++)
			{
				fscanf(fptr, "%s", c);
				training_set[counter].x[i] = (double)atoi(c);
			}
		else
			for(int i = 1; i < 65; i++)
			{
				fscanf(fptr, "%s", c);
				testing_set[counter].x[i] = (double)atoi(c);
			}

			if(flag == TRAINING_DIGIT)						/* set the bias */
				training_set[counter].x[0] = 1.0;	
			else
				testing_set[counter].x[0] = 1.0;	
		counter++;/*increment the counter*/
	}

	fclose(fptr); /*close the file*/

	counter = 0;  /*reinitialize counter*/
	if(flag == TRAINING_DIGIT) /*training digits*/
	{
		mptr = fopen("digit_y.dat", "r");
	}
	else
		mptr = fopen("digit_y_test.dat", "r");

	if( mptr == NULL)
	{
		fprintf(stderr, "Error: The file could not be opened \n");
	}

	//while(!feof(mptr))
	while(counter != digit_counter)
	{
		/*no error chedk so better make sure that your file is not jinxed*/
		if(flag == TRAINING_DIGIT)
		{
			fscanf(mptr, "%s", c);
			training_set[counter].y = (double)atoi(c);
		}
		else
		{
			fscanf(mptr, "%s", c);
			testing_set[counter].y = (double)atoi(c);
		}

		counter++;/*increment the counter*/
	}
	fclose(mptr);

	/*print_digit(training_set[99]);*/
}

/*****************************************************************************/

void print_digit(DIGIT digit)			/* Print formatted digit */
{
  printf("\n");
	for(int i= 1; i < 65; i++)
	{
		if(digit.x[i] == 0)
			printf(" ");
		else
			printf("#");	


		if(i%8  == 1)
		{
			printf(" ");
		}
		if(i%8  == 0)
		{
			printf("\n");
		}

	}
}

/****************************************************************************/

void init_random()
{
  srandom	(time(NULL));
}

/****************************************************************************/

DIGIT get_random_testing_digit()		/* Getting random test cases */
{										/* from the testing set */
	long random_index = 0;	

	random_index = random() % NUM_TEST_DIGS;
	return testing_set[random_index];

}

/***************************************************************************/

DIGIT get_random_training_digit()
{
	int random_index = 0;	

	random_index = random() % NUM_TRAIN_DIGS;
	return training_set[random_index];

}

/***************************************************************************/

DIGIT get_nth_testing_digit(int n)		/* Getting specific test cases */
{
	if(n > NUM_TEST_DIGS)
	{
		printf("Error: Trying to access testing values out of range");	
		exit(0);
	}	
	return testing_set[n];
}

/***************************************************************************/

DIGIT get_nth_training_digit(int n)	
{
	if(n > NUM_TRAIN_DIGS)
	{
		printf("Error: Trying to access training values out of range");	
		exit(0);
	}	
	return training_set[n];
}

/***************************************************************************/

/* reset weights */
void reset_weights(double *weights)
{
for(int i = 0; i < 65; i++)
	{
		weights[i] = 0;	
	}
}


/* copy weights*/
/* weights are assumed to be stored in a double array */
/* weights w_0 (bias) w[1:64] - weights for digit inputs */
void copy_weights(double weights_from[], double weights_to[])
{
for(int l=0; l < 65; l++)
		{
			weights_to[l] = weights_from[l];	
		}
}


/* initializes the digit system */
void init_digits()
{
	init_random();
	read_digit(TRAINING_DIGIT);
	read_digit(TESTING_DIGIT);	
}

/* ********************************************************** */
//make -> digits
/* Part a. */
/* compute probability */
 double compute_probability(double weights[], double x[]) 
 {
	 double e = 2.718281828;
	 double power = weights[0]; 
	 double sum = 0;
	 for(int i = 1; i < 65; i++)
	 {
		sum = sum + weights[i]* x[i];
	 }
	 
	 power = power + sum;
     return (double) 1.0 / (1.0 + pow(e, -power));
 }


/* Part b. */
/*  on-line gradient descent procedure */
 void online_gradient_descent(int iterations) 
 {
	 //double w[65];
	 reset_weights(weights_opt);
	 
	 double alpha;
	 DIGIT randDig;
	 double error = 0;
	 
	 for(int j = 1; j < 65 ; j++)
	 {
		 for(int i = 1; i <= iterations ; i++)
		 {
			 randDig = get_random_training_digit();
			 //alpha = (double) 1.0 / (2.0 * sqrt(iterations)); 
			 alpha = (double) 1.0 / iterations; 
			 error = randDig.y - compute_probability( weights_opt, randDig.x);   
			 weights_opt[j] = weights_opt[j] + alpha * error * randDig.x[j];
		 }
		 printf("%f , ", weights_opt[j]);
	 }	 
 }


/* Part c. */
/*  Classify */
/***** computes the output according to probabilities ***/ 
 int classify(DIGIT digit) 
 {
	 double prob = compute_probability(weights_opt , digit.x);
	 if(prob >= 0.5)
		 return 1; //3
	 else
		 return 0;  //5
 }


/* Part d. */
/* compute the misclassification errors */
void compute_errors()
{
	DIGIT mydigit;
	int yfunc, yreal, count = 0;
	double TrainingError , TestError;
	
	for(int i = 1; i <= NUM_TRAIN_DIGS ; i++)
	{
		mydigit = get_nth_training_digit(i);
		yreal = mydigit.y;
		yfunc = classify(mydigit);
		if(yreal != yfunc)
			count++;
		//yfunc = compute_probability(weights_opt, mydigit.x);
		//error = pow((yreal - yfunc), 2);
		//sum = sum + error;
	}
	
	TrainingError = (double) count / NUM_TRAIN_DIGS;
	printf("\nAvg Training Error = %f\n", TrainingError);
	
	count = 0;
	for(int i = 1; i <= NUM_TEST_DIGS ; i++)
	{
		mydigit = get_nth_testing_digit(i);
		yreal = mydigit.y;
		yfunc = classify(mydigit);
		if(yreal != yfunc)
			count++;
		//yfunc = compute_probability(weights_opt, mydigit.x);
		//error = pow((yreal - yfunc), 2);
		//sum = sum + error;
	}
	
	TestError = (double) count / NUM_TEST_DIGS;
	printf("Avg Test Error = %f\n", TestError);
	
} 


/***************************************************************************/
/* Part e. */
/* main function that runs the online learning and tests for errors */

int main()
{
	init_digits();
	//print_digit(training_set[3]);
    //print_digit(training_set[57]);		
	 online_gradient_descent(1500); 
	 //int myclass = classify(training_set[57]);
	 //printf("%d\n" , myclass);
	compute_errors(); 
	return 0;
}


