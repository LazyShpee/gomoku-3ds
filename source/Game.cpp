#include "../include/Game.hpp"

Game::Game() : TopBg(top_bg_bgr, 0xea00ed), Sprites(sprites_bgr, 0xac00e5), BottomBg(bottom_bg_bgr),
               player(1), lastX(-1), lastY(-1) {
	for (size_t _x = 0; _x < 19; _x++)
		for (size_t _y = 0; _y < 19; _y++)
			board[_x][_y] = 0;
}

Game::~Game() {}

void Game::Draw() {
    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();

    TopScreen.DrawImage(TopBg, 0, 0);
    BottomScreen.DrawImage(BottomBg, 0, 0);

    for (size_t _x = 0; _x < 19; _x++)
        for (size_t _y = 0; _y < 19; _y++)
            if (board[_x][_y])
                BottomScreen.DrawImage(Sprites, BX + _x * 10, BY + _y * 10, (board[_x][_y] - 1) * 10, 0, 10, 10);
}

GameState Game::Update(int dtms, void *dataPtr) {
    // Update inputs
    kDown = hidKeysDown();
	kHeld = hidKeysHeld();

    if (kHeld & KEY_START && kHeld & KEY_SELECT)
        return ST_QUIT; // break in order to return to hbmenu
    else if (kHeld & KEY_SELECT && kDown & KEY_A)
        return ST_NEWGAME;
    else if (kDown & KEY_A)
        for (size_t _x = 0; _x < 19; _x++)
            for (size_t _y = 0; _y < 19; _y++)
                board[_x][_y] = rand() % 3;

    return ST_KEEP;
}