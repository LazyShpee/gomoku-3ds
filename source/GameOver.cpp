#include "../include/GameOver.hpp"

GameOver::GameOver() : TopBg(TopBg_bgr), BottomBg(BottomBg_bgr) {

}

GameOver::~GameOver() {

}

GameState GameOver::Update(int dtms, void *dataPtr) {
    kDown = hidKeysDown();
    if (kDown & KEY_TOUCH) return ST_MENU;
    return ST_KEEP;
}

void GameOver::Draw(void *dataPtr) {
    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();

    TopScreen.DrawImage(TopBg, 0, 0);
    BottomScreen.DrawImage(BottomBg, 0, 0);

}
