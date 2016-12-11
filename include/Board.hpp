#ifndef BOARD_H_
# define BOARD_H_

# include <stdlib.h>

namespace Board {
    typedef struct s_tile {
        int x; // X coord
        int y; // Y coord
        int p; // Piece on tile (0 for none)
        struct s_tile **sides;
        int *dist;
    } t_tile;

    t_tile **makeNewBoard(int w, int h);
    void destroyBoard(t_tile **board, int w, int h);
}

#endif