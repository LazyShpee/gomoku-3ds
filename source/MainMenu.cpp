#include <sstream>
#include "../include/MainMenu.hpp"

# define BTN_X_NEWGAME 60
# define BTN_Y_NEWGAME 10

# define BTN_X_MODE 60
# define BTN_Y_MODE 65

# define BTN_X_RESUME 60
# define BTN_Y_RESUME 120

# define BTN_X_QUIT 60
# define BTN_Y_QUIT 175

MainMenu::MainMenu() :
    TopBg(TopBg_bgr), BottomBg(BottomBg_bgr),
    SailorMars(SailorMars_bgr, 0xa81715), SailorMercury(SailorMercury_bgr, 0x3f64a1),
    Title(Title_bgr, C_ALPHA),
    ButtonBack(ButtonBack_bgr, C_ALPHA),
    FantasqueFont(FantasqueFont_bgr, "?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!,.;:/\\_-()[]{}<>^`|\"'#~& @+=%$£°€*§", C_ALPHA),
    Ma_x(-I_SAILORMARS_W), Me_x(TOP_WIDTH), Title_y(TOP_HEIGHT),
    GameMode(PVP)
    {}

MainMenu::~MainMenu() {

}

GameState MainMenu::Update(int dtms, void *dataPtr) {
    hidTouchRead(&tPos);
    kDown = hidKeysDown();

    if (Ma_x < 0) Ma_x += dtms / 5000;
    if (Me_x > TOP_WIDTH - I_SAILORMERCURY_W) Me_x -= dtms / 5000;
    if (Title_y > TOP_HEIGHT - I_TITLE_H) Title_y -= dtms / 6500;

    if (kDown & KEY_TOUCH) {
        if (BTN_COLLIDE(BTN_X_NEWGAME, BTN_Y_NEWGAME, tPos.px, tPos.py))
            return ST_NEWGAME;
        else if (BTN_COLLIDE(BTN_X_RESUME, BTN_Y_RESUME, tPos.px, tPos.py))
            return ST_RESUME;
        else if (BTN_COLLIDE(BTN_X_MODE, BTN_Y_MODE, tPos.px, tPos.py)) {
            GameMode = (MainMenu::GameModes)(((int)GameMode + 1) % 2);
        } else if (BTN_COLLIDE(BTN_X_QUIT, BTN_Y_QUIT, tPos.px, tPos.py))
            return ST_QUIT;
        else if (tPos.px < 10)
            return ST_GAMEOVER;
    }
    *((int*)dataPtr) = (int)GameMode;
    return ST_KEEP;
}

void MainMenu::Draw(void *dataPtr) {
    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();

    TopScreen.DrawImage(TopBg, 0, 0);
    TopScreen.DrawImage(SailorMercury, Me_x, 0);
    TopScreen.DrawImage(SailorMars, Ma_x, 0);
    TopScreen.DrawImage(Title, 25, Title_y, 0, 0, 0, 0, 0x23AF34);

    BottomScreen.DrawImage(BottomBg, 0, 0);

    BottomScreen.DrawImage(ButtonBack, BTN_X_NEWGAME, BTN_Y_NEWGAME);
    BottomScreen.DrawText(FantasqueFont, BTN_X_NEWGAME + 60, BTN_Y_NEWGAME + 15, "NEW GAME", 0, 0x77FF77);

    BottomScreen.DrawImage(ButtonBack, BTN_X_MODE, BTN_Y_MODE);
    std::string GM(GameMode == PVP ? "Player vs Player" : GameMode == PVI ? "  Player vs IA" : "    IA vs IA");
    BottomScreen.DrawText(FantasqueFont, BTN_X_MODE + 80, BTN_Y_MODE + 5, "MODE:", 0, 0x77FF77);
    BottomScreen.DrawText(FantasqueFont, BTN_X_MODE + 20, BTN_Y_MODE + 25, GM, 0, 0x77FF77);

    BottomScreen.DrawImage(ButtonBack, BTN_X_RESUME, BTN_Y_RESUME);
    BottomScreen.DrawText(FantasqueFont, BTN_X_RESUME + 70, BTN_Y_RESUME + 15, "RESUME", 0, 0x77FF77);

    BottomScreen.DrawImage(ButtonBack, BTN_X_QUIT, BTN_Y_QUIT);
    BottomScreen.DrawText(FantasqueFont, BTN_X_QUIT + 80, BTN_Y_QUIT + 15, "QUIT", 0, 0x77FF77);
}