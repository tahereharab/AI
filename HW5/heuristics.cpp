/**************************************************************/
// Heuristic

#include "heuristics.h"

std::string row_as_string(const TBoard& board, int row)
{
        std::string out("");

        for (int j = 0; j < 10; j++)
            out += board[row][j];

        return out;
}

std::string column_as_string(const TBoard& board, int column)
{
        std::string out("");

        for (int i = 0; i < 10; i++)
            out += board[i][column];

        return out;
}

std::string diag_nw_se_as_string(const TBoard& board, int diag)
{
        std::string out("");

        for (int j = 0; j < 10; j++)
            if ((diag + j - 9 < 10) && (diag + j - 9 >= 0))
                out += board[j][j + diag - 9];

        return out;
}

std::string diag_ne_sw_as_string(const TBoard& board, int diag)
{
        std::string out("");

        for (int j = 0; j < 10; j++)
            if ((diag - j < 10) && (diag - j >= 0))
                out += board[j][diag - j];

        return out;
}

int evalstring(const std::string& line, char mark)
{

        const char* win;
        const char* almostwin;
        const char* threat1;
        const char* threat2;
        const char* threat3;
        const char* good1;
        const char* init1;

        if (mark == 'X')
        {
                win = "XXXXX";
                almostwin = "_XXXX_";
                threat1 = "_XXX_";
                threat2 = "_XX_X_";
                threat3 = "_X_XX_";
                good1 = "_XX_";
                init1 = "___X___";
        }
        else
        {
                win = "OOOOO";
                almostwin = "_OOOO_";
                threat1 = "_OOO_";
                threat2 = "_OO_O_";
                threat3 = "_O_OO_";
                good1 = "_OO_";
                init1 = "___O___";
        }
	
        int score = 0;


        if (line.find(win) != std::string::npos)
        {
                score += 100;
        }
        else if (line.find(almostwin) != std::string::npos)
        {
                score += 75;
        }
        else if (line.find(threat1) != std::string::npos)
        {
                score += 20;
        }
        else if (line.find(threat2) != std::string::npos)
        {
                score += 20;
        }
        else if (line.find(threat3) != std::string::npos)
        {
                score += 20;
        }
        else if (line.find(good1) != std::string::npos)
        {
                score += 5;
        }
        		else if (line.find(init1) != std::string::npos)
	    {
			score += 1;
		}

        return score;

}

int eval(const TBoard& board, char mark)
{
        int score = 0;

        // look for good structures horizontally
        for (int i = 0; i < 10; i++)
        {
            score += evalstring(row_as_string(board, i), mark);
        }

        // look for good structures vertically
        for (int j = 0; j < 10; j++)
        {
            score += evalstring(column_as_string(board, j), mark);
        }

        // look for good structures diagonally
        for (int k = 0; k < 19; k++)
        {
            score += evalstring(diag_nw_se_as_string(board, k), mark);
        }

         // look for good structures diagonally
        for (int k = 0; k < 19; k++)
        {
            score += evalstring(diag_ne_sw_as_string(board, k), mark);
        }

        return score;
}

int eval(const TBoard& board)
{
        return eval(board, 'X') - eval(board, 'O');
}


