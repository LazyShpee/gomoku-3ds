#ifndef IAI_H_
# define IAI_H_

# include "Utils.hpp"
# include "Board.hpp"

class IAI {
    public:
        virtual int EvalPos(Board::t_tile **board, int x, int y, int *score) = 0;
        virtual t_vec think(Board::t_tile **board, int *score, int player, int lvl = 1) = 0;
};

#endif