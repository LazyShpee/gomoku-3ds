#include "../include/AISociable.hpp"

#define INV(d) ((d + 4) % 8)

#define MAX(a, b) a = ((a) > (b) ? (a) : (b))

#define S_CAPTURE 30
#define S_CAPTURE_WIN 100

#define S_PROTECT 20
#define S_FUTURE_PROTECT 0
#define S_PROTECT_WIN 60

#define S_BLOCK_2 20
#define S_BLOCK_BLANK_3 50
#define S_BLOCK_FULL_3 (S_BLOCK_BLANK_3 + 1)

#define S_SELFCHAIN_BONUS 12

#define S_WIN 1000
#define S_CAN_WIN 45

int AISociable::EvalPos(Board::t_tile **board, int x, int y, int *score) {
    int ret = 0, value = 0;
    int p = board[x][y].p;
    int e = INVP(p);
    bool ABORT = false;

    for (int d = 0; d < 8; d++) {
        value = 0;
        if ((board[x][y].sides[d] && board[x][y].sides[d]->p) ||
            (board[x][y].sides[INV(d)] && board[x][y].sides[INV(d)]->p)) {
            char v[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int c = 0;
            value = 1;
            Board::t_tile *tmp = &board[x][y];
            int dd = tmp->dist[INV(d)];
            int da = 18 - dd;
            while (tmp && tmp->sides[INV(d)]) tmp = tmp->sides[INV(d)];
            while (tmp) {
                v[c++] = tmp->p;
                tmp = tmp->sides[d];
            }
            if (da >= 4 && v[dd + 1] == e && v[dd + 2] == e && v[dd + 3] == p) MAX(value, (score[p - 1] >= 6 ? S_CAPTURE_WIN : S_CAPTURE));
            if (da >= 3 && v[dd + 1] == p && v[dd + 2] == p && v[dd + 3] == e) MAX(value, (score[e - 1] >= 6 ? S_PROTECT_WIN : S_PROTECT));
            if (dd >= 1 && da >= 2  && v[dd + 1] == e && v[dd + 2] == e && v[dd - 1] == e) MAX(value, S_BLOCK_BLANK_3);
            if (da >= 4 && v[dd + 1] == e && v[dd + 2] == e && v[dd + 3] == e && v[dd + 4] != p) MAX(value, S_BLOCK_FULL_3);

            if (da >= 2 && v[dd + 1] == e && v[dd + 2] == e) MAX(value, S_BLOCK_2);

            if (da >= 2 && v[dd + 1] == p && v[dd + 2] == p) MAX(value, S_SELFCHAIN_BONUS * 1);
            if (da >= 3 && v[dd + 1] == p && v[dd + 2] == p && v[dd + 3] == p) MAX(value, S_SELFCHAIN_BONUS * 2);
            if (da >= 4 && v[dd + 1] == p && v[dd + 2] == p && v[dd + 3] == p && v[dd + 4] == p) MAX(value, ref._WinningPosition(x, y) == 2 ? S_WIN : S_CAN_WIN);
            if (dd >= 1 && da >= 2  && v[dd + 1] == p && v[dd + 2] == p && v[dd - 1] == p) MAX(value, ref._WinningPosition(x, y) == 2 ? S_WIN : S_CAN_WIN);

            if (value < 100 && dd >= 1 && !v[dd - 1] && da >= 2 && v[dd + 1] == p && v[dd + 2] == e) ABORT = true;
        }
        if (value > ret) ret = value;
    }
    return ABORT ? -1000 : ret;
}

t_vec AISociable::think(Board::t_tile **board, int *score, int player, int lvl) {
    std::vector<t_vec> poses;
    t_vec pos = {rand() % 19, rand() % 19};
    int value = -1;
    Board::t_tile **new_board = Board::makeNewBoard(19, 19);
    ref.setBoard(new_board);
    for (int x = 0; x < 19; x++)
        for (int y = 0; y < 19; y++) {
            Board::restoreBoard(new_board, board, 19, 19);
            if (!board[x][y].p && ref.CanPlace(player, x, y)) {
                new_board[x][y].p = player;
                if (int nvalue = EvalPos(new_board, x, y, score)) {
                    if (nvalue > value) {
                        pos = (t_vec){x, y};
                        value = nvalue;
                        poses.clear();
                        poses.push_back(pos);
                    } else if (nvalue == value) {
                        pos = (t_vec){x, y};
                        poses.push_back(pos);
                    }
                }
            }
        }
    return poses[rand() % poses.size()];
}

AISociable::AISociable() : ref(NULL) {

}

AISociable::~AISociable() {

}

