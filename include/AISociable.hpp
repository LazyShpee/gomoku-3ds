#ifndef AISOCIABLE_H_
# define AISOCIABLE_H_

# include "../include/IAI.hpp"
# include "../include/Board.hpp"
# include "../include/Referee.hpp"

class AISociable : public IAI {
    private:
        Referee ref;
    public:
        int EvalPos(Board::t_tile **board, int x, int y, int *score);
        t_vec think(Board::t_tile **board, int *score, int player, int lvl = 1);
        AISociable();
        virtual ~AISociable();
};

#endif