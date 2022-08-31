#include "tsp.h"
#include "float.h"

/* takes a TSP problem definition 
   and applies the simulated annealing algorithm to it */

   double cooling(int i, int steps, double temp )
{
	double newTemp = (temp/steps)*(steps-i);
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
		int tried_tours , accepted_tours = 0;
		double temp = init_temp;
		double best_energy = FLT_MAX;
		TOUR * initial_tour = generate_random_tour();
		TOUR * best_tour = initial_tour;
		init_energy = energy(tsp_prob, initial_tour);
		curr_energy = init_energy;
		printf("\n\nInitial Tour:   ");
		show_tour(initial_tour);
		printf("\n Initial Energy = %lf\n", init_energy);
		printf("\n Initial temperature = %lf\n", init_temp);
		TOUR * mutation_tour;
		int i = 0;
		while(temp > 1)
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
		
		printf("\n Tried Tours = %ld\n", tried_tours + 1);
		printf("\n Accepted Tours = %ld\n", accepted_tours);
		printf("\n Best Tour's Energy = %lf\n", best_energy);
		printf("\n Best Tour: ");
		show_tour(best_tour);
		
		
		return best_energy;
}


int main()
{
		CITY *tsp_prob;        

		tsp_prob = generate_standard_TSP();
		//sim_anneal(tsp_prob, 400000,30); :102. 719
		//sim_anneal(tsp_prob, 350000,10); 106
		sim_anneal(tsp_prob, 400000,50);
		/*double energy , best;
		int best_number_steps , best_temp = 0;
		best = 100; 
		for(int i=200000; i<450000; i=i+50000)
		{
			for(int j=10; j<100; j=10+j)
			{
				energy = sim_anneal(tsp_prob, i,j);
				if(energy < best)
				{
					best = energy;
					best_number_steps = i;
					best_temp = j;
				}
			}
		}
		
		
			printf("\n Best Energy = %lf\n", best);
			printf("\n best_number_steps = %ld\n", best_number_steps);
			printf("\n best_temp = %ld\n", best_temp);*/
			
		


		return 0; 

}


