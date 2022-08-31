#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "heuristics.h"
#include "types.h"
#include "Tree.h"
#include <time.h>

const int SIZE = 10;

/**************************************************************/
// This represents your response. Update these variables when
// you find a better answer than your current one. Note that
// xcoord indexes rows and ycoord columns!!!

int xcoord = -1;
int ycoord = -1;


/**************************************************************/
// This represents the board. Your player always plays 'X'. Empty
// squares are filled with "_". Your opponent plays "O". This array
// is already filled for you. You can rely on it containing a valid
// board position.

TBoard board;

/**************************************************************/
// STUDENTS: implement your search here in workthread - player() 

void player()
{

		// dumb player: just return some empty position

		// When the time elapses and your player has not produced
		// a valid move, it loses that game. So you want to set the 
		// variables xcoord and ycoord to a at least a valid move 
		// right at the outset!


		bool success = false;

        srand(time(NULL));

        while (!success)
        {
                int i = rand() % 10;
                int j = rand() % 10;

                if (board[i][j] == '_')
                {
                        xcoord = i;
                        ycoord = j;
                        success = true;
                }

        }

		// initialize tree
		Tree st(board);
            // run minimax
		int move = st.minimax(2);
            // record the coordinates of the move
		xcoord = move / 10;
		ycoord = move % 10;

};

/**************************************************************/
// displays the current board position

void displayboard()
{
		for (int i = 0; i < SIZE; i++)
		{
				for (int j = 0; j < SIZE; j++)
				{
						std::cout << board[i][j] << " ";
				}

				std::cout << std::endl;
		}

		std::cout << "end" << std::endl;

};



/***************************************************************/
// STUDENTS: please do not modify main()
int main(int argc, char* argv[])
{

		// Load the board position
		board.resize(SIZE);
		for (int i = 0; i < SIZE; i++)
		{
				board[i].resize(SIZE);
				for (int j = 0; j < SIZE; j++)
				{
						std::cin >> board[i][j];
						std::ws(std::cin);
				}
		};

		player();

		// produce the result, whatever it may be
		std::cout << xcoord << ycoord << std::endl;
		return 0;
}




