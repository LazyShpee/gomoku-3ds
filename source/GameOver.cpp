#include "../include/GameOver.hpp"

GameOver::GameOver() : TopBg(TopBg_bgr), BottomBg(BottomBg_bgr),
    SailorMarsBig(SailorMarsBig_bgr, 0xa81715), SailorMercuryBig(SailorMercuryBig_bgr, 0x3f64a1),
    FantasqueFont(FantasqueFont_bgr, "?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!,.;:/\\_-()[]{}<>^`|\"'#~& @+=%$£°€*§", C_ALPHA),
    textTaint(-1)
{

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
    if (*((int *)dataPtr) == 1) TopScreen.DrawImage(SailorMercuryBig, 60, 0);
    else TopScreen.DrawImage(SailorMarsBig, 60, 0);
    BottomScreen.DrawText(FantasqueFont, 30, 105, "Touch to go back to main menu", textTaint);
}
