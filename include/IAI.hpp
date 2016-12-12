#ifndef IAI_H_
# define IAI_H_

# include "Utils.hpp"
# include "Board.hpp"

class IAI {
    public:
        virtual t_vec think(Board::t_tile **board, int lvl = 1) = 0;
};

#endif