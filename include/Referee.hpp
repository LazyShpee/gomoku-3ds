#ifndef REFEREE_H_
# define REFEREE_H_

static int s_direction[8][2] = { {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0} };

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
	char (& board)[19][19];

        char vision(char *v, char x, char y, char direction, bool lookBack = false);
    public:
	Referee(char (& board)[19][19]);
        virtual ~Referee();
        bool CanPlace(char player, char x, char y);
        bool UpdateBoard(char x, char y);
};

#endif // !REFEREE_H_

/*
**  1 2 3
**  8   4
**  7 6 5
*/
