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
    t_tile **makeNewBoard(char **board, int w, int h);
    t_tile **makeNewBoard(t_tile **board, int w, int h);
    void destroyBoard(t_tile **board, int w, int h);
    void destroyBoard(char **board, int w, int h);
    void restoreBoard(t_tile **board, char **save, int w, int h);
    void restoreBoard(t_tile **board, t_tile **save, int w, int h);
    void saveBoard(t_tile **board, char **save, int w, int h);
    char **saveBoard(t_tile **board, int w, int h);
}

#endif