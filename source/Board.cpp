#include "../include/Board.hpp"

static int directions[8][2] = {
        {-1, -1},
        {0, -1},
        {1, -1},
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0}
    };

Board::t_tile **Board::makeNewBoard(int w, int h) {
    t_tile **board;

    board = (t_tile **)malloc(sizeof(t_tile *) * w);
    for (int x = 0; x < w; x++) {
        board[x] = (t_tile *)malloc(sizeof(t_tile) * h);
        for (int y = 0; y < h; y++) {
            t_tile *cur = &board[x][y];
            cur->x = x;
            cur->y = y;
            cur->p = 0;
            cur->sides = (t_tile **)malloc(sizeof(t_tile *) * 8);
            cur->dist = (int *)malloc(sizeof(int) * 8);
            for (int s = 0; s < 8; s++) {
                int _x = 18, _y = 18;
                if (directions[s][0] < 0) _x = x;
                else if (directions[s][0] > 0) _x = w - x - 1;
                if (directions[s][1] < 0) _y = y;
                else if (directions[s][1] > 0) _y = h - y - 1;
                cur->dist[s] = _x > _y ? _y : _x;
                cur->sides[s] = NULL;
            }
        }
    }
    for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
            for (int s = 0; s < 8; s++) {
                t_tile *cur = &board[x][y];
                int dx = directions[s][0], dy = directions[s][1];
                if (((dx < 0 && x > 0) || (dx > 0 && x < w - 1) || !dx) &&
                    ((dy < 0 && y > 0) || (dy > 0 && y < h - 1) || !dy))
                    cur->sides[s] = &board[x + dx][y + dy];
            }

    return board;
}

Board::t_tile **Board::makeNewBoard(char **board, int w, int h) {
    t_tile **newBoard = makeNewBoard(w, h);
    restoreBoard(newBoard, board, w, h);
    return  newBoard;
}

Board::t_tile **Board::makeNewBoard(Board::t_tile **board, int w, int h) {
    t_tile **newBoard = makeNewBoard(w, h);
    restoreBoard(newBoard, board, w, h);
    return  newBoard;
}

void Board::destroyBoard(Board::t_tile **board, int w, int h) {
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            free(board[x][y].sides);
            free(board[x][y].dist);
        }
        free(board[x]);
    }
    free(board);
}

void Board::destroyBoard(char **board, int w, int h) {
    for (int x = 0; x < w; x++) {
        free(board[x]);
    }
    free(board);
}

void Board::restoreBoard(Board::t_tile **board, char **save, int w, int h) {
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            board[x][y].p = save[x][y];
        }
    }
}

void Board::restoreBoard(Board::t_tile **board, Board::t_tile **save, int w, int h) {
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            board[x][y].p = save[x][y].p;
        }
    }
}

void Board::saveBoard(Board::t_tile **board, char **save, int w, int h) {
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            save[x][y] = board[x][y].p;
        }
    }
}

char ** Board::saveBoard(Board::t_tile **board, int w, int h) {
    char **save = (char **)malloc(sizeof(char *) * w);
    for (int x = 0; x < w; x++) {
        save[x] = (char *)malloc(sizeof(char) * h);
        for (int y = 0; y < h; y++) {
            save[x][y] = board[x][y].p;
        }
    }
    return save;
}