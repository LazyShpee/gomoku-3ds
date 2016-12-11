#ifndef BOARD_H_
# define BOARD_H_

# include <stdlib.h>

namespace Board {

    static int directions[8][2] = {
        {-1, -1},
        {0, -1},
        {1, -1},
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0}
    };

    typedef struct s_tile {
        int x; // X coord
        int y; // Y coord
        int p; // Piece on tile (0 for none)
        struct s_tile **sides;
    } t_tile;

    t_tile **makeNewBoard(int w, int h);
    void destroyBoard(t_tile **board, int w, int h);
}

#endif