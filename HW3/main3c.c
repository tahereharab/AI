#include "tsp.h"
#include "float.h"
#include "math.h"

/* takes a TSP problem definition 
   and applies the simulated annealing algorithm to it */

   double cooling(int i, int steps, double temp )
{
	double newTemp = temp/(1+100*log(1+i));  //logarithmic
	//double newTemp = temp*pow(0.9, i);  //exponential
	//double newTemp = temp/(1+0.3*pow(i,2));  //Quadratic 

	return newTemp;
}

int probabilistic(double init_energy , double mut_energy, double temp)
{
	double randum_number=(double) (rand()/ (double) RAND_MAX);
	double gain = abs(mut_energy - init_energy);
	double prob = exp(-gain/temp);
    if(prob >= 	randum_number)
		return 1;
	else
		return 0;	
}

double sim_anneal(CITY * tsp_prob,int cc, double init_temp)
{
		double init_energy , curr_energy , next_energy = 0;
		int tried_tours = 1;
		int accepted_tours = 0;
		double temp = init_temp;
		double best_energy = FLT_MAX;
		TOUR * initial_tour = generate_random_tour();
		TOUR * best_tour = initial_tour;
		init_energy = energy(tsp_prob, initial_tour);
		curr_energy = init_energy;
		//printf("\n\nInitial Tour:   ");
		//show_tour(initial_tour);
		//printf("\n Initial Energy = %lf\n", init_energy);
		//printf("\n Initial temperature = %lf\n", init_temp);
		TOUR * mutation_tour;
		int i = 0;
		while(tried_tours < 20001)
		{
			mutation_tour = generate_mutation(initial_tour);	
			tried_tours++;
			next_energy = energy(tsp_prob, mutation_tour);
			if(next_energy < curr_energy)	
			{				
				initial_tour = mutation_tour;
				curr_energy = next_energy;
				accepted_tours++;				
			}
			else
			{
				if(probabilistic(curr_energy , next_energy, temp) == 1)	
				{					
					initial_tour = mutation_tour;	
					curr_energy = next_energy;
					accepted_tours++;					
				}									
			}
			
			temp = cooling(i, cc, init_temp);	
			i++;			
			if(curr_energy < best_energy)
			{
				best_energy = curr_energy;
				best_tour = initial_tour;
			}
		}
		
		//printf("\n Tried Tours = %ld\n", tried_tours);
		//printf("\n Accepted Tours = %ld\n", accepted_tours);
		//printf("\n Best Tour's Energy = %lf\n", best_energy);
		//printf("\n Best Tour: ");
		//show_tour(best_tour);
		
		
		return best_energy;
}


int main()
{
		CITY *tsp_prob;        
		double avg_energy , sum_energy = 0;
		tsp_prob = generate_standard_TSP();
		for(int i = 0; i<20; i++)
		{
			sum_energy += sim_anneal(tsp_prob, 250000,200); 
		}
		avg_energy = sum_energy/20;
		printf("\n Average Energy = %lf\n", avg_energy);
		
		return 0; 

}


