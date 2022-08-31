#ifndef _Tree_h_
#define _Tree_h_

#include <vector>
#include <list>
#include "types.h"

class Tree
{
		public:

			Tree(const TBoard& brd);
			Tree(Tree* parent, const TBoard& brd, int depth, bool min, int move);

			void expand();

			// drop all children
			void drop_children();

			// run minimax algorithm
			int minimax(int maxdpth);
			void minimax_propag(int maxdpth);

			// evaluate this node using heuristic
			void eval();
			
			// accessors
			inline bool Minimizing() const;

			// returns the state of definiteness for the value contained
			// 0 = we don't know
			// 1 = we have a corresponding bound
			// 2 = we have a result
			inline int Definite() const;

			inline int Value() const;

			inline Tree* Parent() const;

			inline int Move() const;

		private:

			// state stored in this node
			TBoard state;

			// what the move was that led here
			int move;

			Tree* parent;

			// list of children
			std::list< Tree > children;

			// depth in the tree		
			int depth;

			// whether this is at the minimizer or maximizer level
			// this also stores whose turn it is since player
			// is always maximizing
			bool min;

			// whether the value is definite ( can be <> )
			int value_definite;

			// value stored
			int value;

}; // end class

// drop all children
inline void Tree::drop_children()
{
		children.clear();
}

// accessors
inline bool Tree::Minimizing() const
{
		return min;
}

inline int Tree::Definite() const 
{
		return value_definite;
}

inline int Tree::Value() const
{
		return value;
}

inline int Tree::Move() const
{
		        return move;
}
#endif

