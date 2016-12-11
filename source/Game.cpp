#include <sstream>
#include "../include/Game.hpp"

Game::Game() :
    TopBg(TopBg_bgr, 0xea00ed), BottomBg(BottomBg_bgr), Sprites(Sprites_bgr, 0xac00e5),
    Goban(Goban_bgr), FantasqueFont(FantasqueFont_bgr, "?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!,.;:/\\_-()[]{}<>^`|\"'#~& @+=%$£°€*§", C_ALPHA),
    board(Board::makeNewBoard(19, 19)), player(1), lastX(-1), lastY(-1) {}

Game::~Game() {
    Board::destroyBoard(board, 19, 19);
}

GameState Game::Update(int dtms, void *dataPtr) {
    // Update inputs
    kDown = hidKeysDown();
	kHeld = hidKeysHeld();
    hidTouchRead(&tPos);

    if (kDown & KEY_TOUCH) // Touch down event
        if (tPos.px >= 65 && tPos.px <= 254 && tPos.py >= 25 && tPos.py <= 214) { // Check cursor in board
            px = (tPos.px - 65) / 10; // Intersect X
            py = (tPos.py - 25) / 10; // Intersect Y
            board[px][py].p = player;
            player = !(player - 1) + 1;
        }

    if (kHeld & KEY_START && kHeld & KEY_SELECT)
        return ST_QUIT; // break in order to return to hbmenu
    else if (kHeld & KEY_SELECT && kDown & KEY_A)
        return ST_MENU;
    else if (kDown & KEY_A)
        for (size_t _x = 0; _x < 19; _x++)
            for (size_t _y = 0; _y < 19; _y++)
                board[_x][_y].p = rand() % 3;

    return ST_KEEP;
}

void Game::Draw(void *dataPtr) {
    char v[20];

    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();

    std::stringstream dbg;
    dbg << px << " - " << py;
    TopScreen.DrawImage(TopBg, 0, 0);
    BottomScreen.DrawImage(BottomBg, 0, 0);
    TopScreen.DrawText(FantasqueFont, 5, 5, dbg.str());
    BottomScreen.DrawImage(Goban, 59, 19);

    for (size_t _x = 0; _x < 19; _x++)
        for (size_t _y = 0; _y < 19; _y++)
            if (board[_x][_y].p)
                BottomScreen.DrawImage(Sprites, BX + _x * 10, BY + _y * 10, (board[_x][_y].p - 1) * 10, 0, 10, 10);
    for (int d = 0; d < 8; d++) {
        int x = 0;
        Board::t_tile *tmp = &board[px][py];
        while (tmp) {
            v[x++] = tmp->p + 48;
            tmp = tmp->sides[d];
        }
        v[x] = 0;
        TopScreen.DrawText(FantasqueFont, 0, 40 + d * 14, std::string(v));
    }
}
