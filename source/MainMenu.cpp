#include "../include/MainMenu.hpp"

MainMenu::MainMenu() : FontTest(font_test_bgr, "abcdefghi ", C_ALPHA) {}

MainMenu::~MainMenu() {

}

GameState MainMenu::Update(int dtms, void *dataPtr) {

    return ST_KEEP;
}

void MainMenu::Draw() {
    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();
    TopScreen.Fill(0xFFFFFF);
    BottomScreen.Fill(0xFFFFFF);
    TopScreen.DrawText(FontTest, 10, 10, "feed a dice", 4, 0xFF0000);
}