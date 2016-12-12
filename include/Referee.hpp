#ifndef REFEREE_H_
# define REFEREE_H_

# include "../include/Board.hpp"

# define INVP(p) (p == 1 ? 2 : 1)

class Referee {
protected:
	Board::t_tile **board;
	bool DoubleThree(char player, int x, int y);
	bool Three(char player, int x, int y, int dir);
public:
	int WinningPosition(int x, int y);
        char vision(char *v, int x, int y, int direction, bool lookBack = false);
	Referee(Board::t_tile **board);
        virtual ~Referee();
        bool CanPlace(char player, int x, int y);
        bool UpdateBoard(int x, int y, int *scores);
};

#endif // !REFEREE_H_

/*
**  1 2 3
**  8   4
**  7 6 5
*/
