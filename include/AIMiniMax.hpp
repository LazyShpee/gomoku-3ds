#ifndef AIMINIMAX_H_
# define AIMINIMAX_H_

# include "../include/IAI.hpp"
# include "../include/Board.hpp"
# include "../include/Referee.hpp"

class AIMiniMax : public IAI {
protected:
  Referee ref;
  int EvalPos(Board::t_tile **board, int x, int y, int *score);
  t_vec maxValue(int *result, int lvl);
  t_vec MiniMax(Board::t_tile **board, int *score, int player, int depth, int lvl);
public:
  AIMiniMax();
  virtual ~AIMiniMax();
  t_vec think(Board::t_tile **board, int *score, int player, int lvl = 1);
};

#endif
