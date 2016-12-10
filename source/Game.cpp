#include <sstream>
#include "../include/Game.hpp"

Game::Game() :
    TopBg(TopBg_bgr, 0xea00ed), BottomBg(BottomBg_bgr), Sprites(Sprites_bgr, 0xac00e5),
    Goban(Goban_bgr), FantasqueFont(FantasqueFont_bgr, "?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!,.;:/\\_-()[]{}<>^`|\"'#~& @+=%$£°€*§", C_ALPHA),
    player(1), lastX(-1), lastY(-1), ref(board) {
	for (size_t _x = 0; _x < 19; _x++)
		for (size_t _y = 0; _y < 19; _y++)
			board[_x][_y] = 0;
}

Game::~Game() {}

GameState Game::Update(int dtms, void *dataPtr) {
    // Update inputs
    kDown = hidKeysDown();
	kHeld = hidKeysHeld();
    hidTouchRead(&tPos);

    if (kDown & KEY_TOUCH) // Touch down event
        if (tPos.px >= 65 && tPos.px <= 254 && tPos.py >= 25 && tPos.py <= 214) { // Check cursor in board
            px = (tPos.px - 65) / 10; // Intersect X
            py = (tPos.py - 25) / 10; // Intersect Y
            if (ref.CanPlace(player, px, py)) {
                board[px][py] = player;
                player = !(player - 1) + 1;
            }
        }

    if (kHeld & KEY_START && kHeld & KEY_SELECT)
        return ST_QUIT; // break in order to return to hbmenu
    else if (kHeld & KEY_SELECT && kDown & KEY_A)
        return ST_MENU;
    else if (kDown & KEY_A)
        for (size_t _x = 0; _x < 19; _x++)
            for (size_t _y = 0; _y < 19; _y++)
                board[_x][_y] = rand() % 3;

    return ST_KEEP;
}

void Game::Draw(void *dataPtr) {
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
            if (board[_x][_y])
                BottomScreen.DrawImage(Sprites, BX + _x * 10, BY + _y * 10, (board[_x][_y] - 1) * 10, 0, 10, 10);
}