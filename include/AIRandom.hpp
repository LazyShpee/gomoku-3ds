#ifndef AIRANDOM_H_
# define AIRANDOM_H_

# include "IAI.hpp"

class AIRandom : public IAI {
    public:
        AIRandom();
        virtual ~AIRandom();
        t_vec think(Board::t_tile **board, int lvl = 1);
};

#endif