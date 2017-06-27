#ifndef GAMESTATES_H_
# define GAMESTATES_H_

enum GameState {
    ST_KEEP,
    ST_QUIT,
    ST_NEWGAME,
    ST_RESUME,
    ST_MENU,
    ST_GAMEOVER
};

typedef struct {
    char player;
    bool gameInProgress;
} gameState;

#endif