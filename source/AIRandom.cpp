#include <stdlib.h>
#include "../include/AIRandom.hpp"

AIRandom::AIRandom() {}
AIRandom::~AIRandom() {}
t_vec AIRandom::think(Board::t_tile **board, int lvl) {
    t_vec ret = {rand()%19, rand()%19};
    return ret;
}