#include "../include/MainMenu.hpp"

MainMenu::MainMenu() : FontTest(font_test_bgr, "abcdefghi ", 0) {}

MainMenu::~MainMenu() {

}

GameState MainMenu::Update(int dtms, void *dataPtr) {

    return ST_KEEP;
}

void MainMenu::Draw() {
    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();
    TopScreen.Fill(0x999999);
    BottomScreen.Fill(0x999999);
    TopScreen.DrawText(FontTest, 10, 10, "feed a dice", 4, 0);
}