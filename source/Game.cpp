#include <sstream>
#include "../include/Game.hpp"

#define LEFT_X 5
#define MENU_Y 5
#define EDIT_Y 55
#define SWAP_Y 185

#define RIGHT_X 295
#define BLANK_Y 5
#define BLUE_Y 55
#define RED_Y 105

Game::Game() :
    TopBg(TopBg_bgr, 0xea00ed), BottomBg(BottomBg_bgr),
    Sprites(Sprites_bgr, 0xac00e5), Buttons(ButtonsGame_bgr, C_ALPHA), Goban(Goban_bgr), ScoreBoard(ScoreBoard_bgr, C_ALPHA),
    SailorMars(SailorMars_bgr, 0xa81715), SailorMercury(SailorMercury_bgr, 0x3f64a1),
    FantasqueFont(FantasqueFont_bgr, "?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!,.;:/\\_-()[]{}<>^`|\"'#~& @+=%$£°€*§", C_ALPHA),
    ScoreFont(ScoreFont_bgr, "0123456789", C_ALPHA),
    board(Board::makeNewBoard(19, 19)), player(1), ref(board),
    px(0), py(0), mode(0), piece(0)
{
    scores = (int *)malloc(sizeof(int) * 2);
    scores[0] = scores[1] = 0;
}

Game::~Game() {
    Board::destroyBoard(board, 19, 19);
}

GameState Game::Update(int dtms, void *dataPtr) {
    // Update inputs
    kDown = hidKeysDown();
	kHeld = hidKeysHeld();
    hidTouchRead(&tPos);

        int cx = tPos.px, cy = tPos.py;
        if (tPos.px >= 65 && tPos.px <= 254 && tPos.py >= 25 && tPos.py <= 214) { // Check cursor in board
            px = (tPos.px - 65) / 10; // Intersect X
            py = (tPos.py - 25) / 10; // Intersect Y
            if (!mode && kDown & KEY_TOUCH) { // Touch down event
                if (ref.CanPlace(player, px, py)) {
                    board[px][py].p = player;
                    if (ref.UpdateBoard(px, py, scores) || scores[1] >= 10 || scores[0] >= 10) {
                        *((int *)dataPtr) = player;
                        return ST_GAMEOVER;
                    }
                    player = !(player - 1) + 1;
                }
            } else if (mode && kHeld & KEY_TOUCH) board[px][py].p = piece;
        }
        if (kDown & KEY_TOUCH) {
            if (BUT_HIT(LEFT_X, MENU_Y, cx, cy)) return ST_MENU;
            else if (BUT_HIT(LEFT_X, EDIT_Y, cx, cy)) mode = !mode;
            else if (mode && BUT_HIT(LEFT_X, SWAP_Y, cx, cy)) player = INVP(player);
            else if (mode && BUT_HIT(RIGHT_X, BLANK_Y, cx, cy)) piece = 0;
            else if (mode && BUT_HIT(RIGHT_X, BLUE_Y, cx, cy)) piece = 1;
            else if (mode && BUT_HIT(RIGHT_X, RED_Y, cx, cy)) piece = 2;
        }
    return ST_KEEP;
}

void Game::Draw(void *dataPtr) {
    TopScreen.GetFrameBuffer();
    BottomScreen.GetFrameBuffer();

    TopScreen.DrawImage(TopBg, 0, 0);
    BottomScreen.DrawImage(BottomBg, 0, 0);

    TopScreen.DrawImage(SailorMars, 0, 0, 0, 0, 0, 0, player == 2 ? -1 : 0);
    TopScreen.DrawImage(SailorMercury, TOP_WIDTH - I_SAILORMERCURY_W, 0, 0, 0, 0, 0, player == 1 ? -1 : 0);

    TopScreen.DrawImage(ScoreBoard, 135, 92);
    std::stringstream score;
    score << (scores[0] < 10 ? "0" : "")  << scores[0];
    TopScreen.DrawText(ScoreFont, 217, 100, score.str());
    score.str( std::string() );
    score << (scores[1] < 10 ? "0" : "") << scores[1];
    TopScreen.DrawText(ScoreFont, 147, 100, score.str());



    BottomScreen.DrawImage(Goban, 59, 19);
    BottomScreen.DrawImage(Buttons, LEFT_X, MENU_Y, 0, 0, 50, 50);
    BottomScreen.DrawImage(Buttons, LEFT_X, MENU_Y, 100, 0, 50, 50);
    BottomScreen.DrawImage(Buttons, LEFT_X, EDIT_Y, 0 + mode * 50, 0, 50, 50);
    BottomScreen.DrawImage(Buttons, LEFT_X, EDIT_Y + mode, 150, 0, 50, 50);

    if (mode == 1) {
        BottomScreen.DrawImage(Buttons, LEFT_X, SWAP_Y, 0, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, LEFT_X, SWAP_Y, 250, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, LEFT_X + 25, SWAP_Y, 325, 0, 50, 50);

        BottomScreen.DrawImage(Buttons, RIGHT_X - 20 * (piece == 0), BLANK_Y, 0, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, RIGHT_X - 20 * (piece == 0), BLANK_Y, 200, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, RIGHT_X - 20 * (piece == 1), BLUE_Y, 0, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, RIGHT_X - 20 * (piece == 1), BLUE_Y, 250, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, RIGHT_X - 20 * (piece == 2), RED_Y, 0, 0, 50, 50);
        BottomScreen.DrawImage(Buttons, RIGHT_X - 20 * (piece == 2), RED_Y, 300, 0, 50, 50);
    }

    int ret = ref.WiningPosition(px, py);
    std::stringstream ret_v;
    ret_v << ret;
    TopScreen.DrawText(FantasqueFont, 1, 60, ret_v.str());

    for (size_t _x = 0; _x < 19; _x++)
        for (size_t _y = 0; _y < 19; _y++)
            if (board[_x][_y].p)
                BottomScreen.DrawImage(Sprites, BX + _x * 10, BY + _y * 10, (board[_x][_y].p - 1) * 10, 0, 10, 10);
}
