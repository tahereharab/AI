#ifndef _heuristics_h_
#define _heuristics_h_

/**************************************************************/
// Heuristic

#include <string>
#include "types.h"

std::string row_as_string(const TBoard& board, int row);

std::string column_as_string(const TBoard& board, int column);

std::string diag_nw_se_as_string(const TBoard& board, int diag);

std::string diag_ne_sw_as_string(const TBoard& board, int diag);

int evalstring(const std::string& line, char mark);

int eval(const TBoard& board, char mark);

int eval(const TBoard& board);

#endif
