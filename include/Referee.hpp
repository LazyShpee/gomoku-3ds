#ifndef REFEREE_H_
# define REFEREE_H_

class Referee {
    protected:
        char **board;

        char vision(char *v, char x, char y, char direction, bool lookBack = false);
    public:
        Referee(char board[19][19]);
        virtual ~Referee();
        bool CanPlace(char player, char x, char y);
        bool UpdateBoard(char x, char y);
};

#endif // !REFEREE_H_

/*
**  6 7 8
**  5   1
**  4 3 2
*/