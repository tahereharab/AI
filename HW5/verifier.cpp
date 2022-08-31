// Verifier, do not modify

#include <iostream>
#include <vector>
#include <fstream>

const int SIZE = 10;

std::vector< std::vector< char > > board;

void displayboard(std::ostream& o)
{
        for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                    o << board[i][j] << " ";
                }

                o << std::endl;
        }

		o << "end" << std::endl;

};

bool Draw()
{
	// all squares are full

	for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                    if (board[i][j] == '_')
					{
						return false;
					}
                }
        }
	
	return true;
}

bool check_position(int i, int j)
{
	// there must be a middle position

	if (board[i][j] != 'X') return false;

	if (	(i+1 < SIZE) && (board[i+1][j] == 'X')	&&
			(i+2 < SIZE) && (board[i+2][j] == 'X')	&&
			(i-1 >= 0) && (board[i-1][j] == 'X')		&&
			(i-2 >= 0) && (board[i-2][j] == 'X')
		)
	{
		return true;
	};

	if (   	(j+1 < SIZE) && (board[i][j+1] == 'X')    &&
            (j+2 < SIZE) && (board[i][j+2] == 'X')    &&
            (j-1 >= 0) && (board[i][j-1] == 'X')     &&
            (j-2 >= 0) && (board[i][j-2] == 'X')
        )
    {
        return true;
    };

 	if (   	(i+1 < SIZE) && (j+1 < SIZE) && (board[i+1][j+1] == 'X')    &&
           	(i+2 < SIZE) && (j+2 < SIZE) && (board[i+2][j+2] == 'X')    &&
           	(i-1 >= 0)  && (j-1 >= 0)  && (board[i-1][j-1] == 'X')   &&
          	(i-2 >= 0)  && (j-2 >= 0)  && (board[i-2][j-2] == 'X')
        )
    {
        return true;
    };

	if (    (i+1 < SIZE) && (j-1 >= 0) && (board[i+1][j-1] == 'X')    &&
            (i+2 < SIZE) && (j-2 >= 0) && (board[i+2][j-2] == 'X')    &&
            (i-1 >= 0)  && (j+1 < SIZE)  && (board[i-1][j+1] == 'X')   &&
            (i-2 >= 0)  && (j+2 < SIZE)  && (board[i-2][j+2] == 'X')
        )
    {
        return true;
    };


	return false;

}

// decide if anybody won
bool Xwon()
{
	for (int i = 0; i < SIZE; i++)
        {
                for (int j = 0; j < SIZE; j++)
                {
                    if (check_position(i,j))
                    {
                        return true;
                    }
                }
        }

	return false;
}

// decide if anybody won
void flipboard()
{

	 for (int i = 0; i < SIZE; i++)
     	{
                for (int j = 0; j < SIZE; j++)
                {
                    if (board[i][j] == 'X')
                    {
                        board[i][j] = 'O';
                    }
					else if (board[i][j] == 'O')
					{
						board[i][j] = 'X';
					}
                }
        }
	
}

int main(int argc, char* argv[])
{

		if (argc != 4)
        {
                std::cout << "Use with 3 arguments: move infile outfile" << std::endl;
                return SIZE;
        }

		int move = atoi(argv[1]);	

		std::ifstream in(argv[2]);
		std::ofstream out(argv[3]);

		// Load the board position
        board.resize(SIZE);
        for (int i = 0; i < SIZE; i++)
        {
                board[i].resize(SIZE);
                for (int j = 0; j < SIZE; j++)
                {
                        in >> board[i][j];
                        std::ws(in);
                }
        };		

		// make the move
		if (board[move/SIZE][move % SIZE] == '_')
		{
			board[move/SIZE][move % SIZE] = 'X';
		}
		else
		{
			// he who makes an invalid move loses
			std::cout << "0" << std::endl;
			return 0;
		}

		// decide if anybody won
		if (Xwon())
		{
			std::cout << "2" << std::endl;
            return 0;
		}

		if (Draw())
		{
			std::cout << "1" << std::endl;
            return 0;	
		}

		// flip the board for the next player
		flipboard();

		// print it
		displayboard(out);

		in.close();
		out.close();

		std::cout << "5" << std::endl;
        
		return 0;
}
		
