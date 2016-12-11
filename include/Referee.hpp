#ifndef REFEREE_H_
# define REFEREE_H_

# include "../include/Board.hpp"

typedef enum direction {
  NORTH_WEST,
  NORTH,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
} e_direction;

class Referee {
protected:
	Board::t_tile **board;

    public:
        char vision(char *v, int x, int y, int direction, bool lookBack = false);
	Referee(Board::t_tile **board);
        virtual ~Referee();
        bool CanPlace(char player, int x, int y);
        bool UpdateBoard(int x, int y);
};

#endif // !REFEREE_H_

/*
**  1 2 3
**  8   4
**  7 6 5
*/
