#include <stdlib.h>
#include "../include/AIRandom.hpp"

AIRandom::AIRandom() {}
AIRandom::~AIRandom() {}
t_vec AIRandom::think(Board::t_tile **board, int *score, int player, int lvl) {
    return (t_vec){rand()%19, rand()%19};
}