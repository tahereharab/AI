#include "Tree.h"
#include "heuristics.h"
#include <iostream>
#include <time.h>

Tree::Tree(const TBoard& brd) :
	state(brd),
	move(-10),
	parent(0),
	depth(0),
	min(false),
	value_definite(0),
	value(0)
{
		
}

Tree::Tree(Tree* prnt, const TBoard& brd, int dpth, bool mn, int mv) : 
	state(brd),
	move(mv),
	parent(prnt),
	depth(dpth),
	min(mn),
	value_definite(0),
	value(0)
{
}

//-------------------------------------------------------------------------
void Tree::expand()
{

	children.clear();

	for (unsigned int i = 0; i < state.size(); i++)
	{
			for (unsigned int j = 0; j < state.size(); j++)
			{
					if (state[i][j] == '_')
					{
							if (min)
							{
									state[i][j] = 'O';
							}
							else
							{
									state[i][j] = 'X';
							}

							children.push_back(Tree(this, state, depth+1, !min, 10*i + j));

							state[i][j] = '_';
					}
			}
	}
}

int Tree::minimax(int maxdpth)
{

	int best = -10;
        int n=0;
        int rresult; 
        
        // initialize a random number generator
	srand(time(NULL));

	minimax_propag(maxdpth);

	int collect;
	if (min)
	{
			collect = 1000 * 1000;
	}
	else
	{
			collect = - 1000 * 1000;
	}
	
	for (std::list<Tree>::const_iterator it = children.begin(); it != children.end(); ++it)
	{
			if (it->Value() == value)
			{
					n++;
                                        rresult=rand() % n;
					if (rresult == 0) {best = it->Move();}
			}
	}

	return best;
}


//-------------------------------------------------------------------------

void Tree::minimax_propag(int maxdpth)
{
		// at maximum depth, use heuristics
		if (depth >= maxdpth)
		{	
			eval();
			return;
		}

		expand();

		int collect;
		if (min)
		{
				collect = 1000 * 1000;
		}
		else
		{
				collect = - 1000 * 1000;
		}

		// go thru the chilren
		for (std::list<Tree>::iterator it = children.begin(); it != children.end(); ++it)
		{
				it->minimax_propag(maxdpth);

				int childval = it->Value();

				if (min)
				{
						collect = (collect < childval) ? collect : childval;

				}
				else
				{
						collect = (collect > childval) ? collect : childval;
				}
		}	 

		value = collect;

}

void Tree::eval()
{
		value = ::eval(state);

}
