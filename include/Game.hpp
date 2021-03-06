#ifndef GAME_H_
# define GAME_H_

# include <3ds.h>
# include <stdlib.h>

# include "../include/GameState.hpp"
# include "../include/IFrame.hpp"
# include "../include/Graphics.hpp"
# include "../include/Referee.hpp"
# include "../include/Board.hpp"
# include "../include/AIRandom.hpp"
# include "../include/AIMiniMax.hpp"
# include "../include/AISociable.hpp"

# define BX 65 // Board Start X position
# define BY 25 // Board Start Y position


#define BUT_HIT(x, y, cx, cy) (cx < x + I_BUTTONSGAME_H && cx > x && cy < y + I_BUTTONSGAME_H && cy > y)

class Game : public IFrame {
    protected:
        /* Inputs */
        u32 kDown;
        u32 kUp;
        u32 kHeld;
        touchPosition tPos;

        /* Screens */
        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_RIGHT> TopScreen2;
        Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;

        /* Images */
        Image<I_TOPBG_W, I_TOPBG_H> TopBg;
    	Image<I_BOTTOMBG_W, I_BOTTOMBG_H> BottomBg;
	    Image<I_SPRITES_W, I_SPRITES_H> Sprites;
	    Image<I_BUTTONSGAME_W, I_BUTTONSGAME_H> Buttons;
	    Image<I_GOBAN_W, I_GOBAN_H> Goban;
	    Image<I_SCOREBOARD_W, I_SCOREBOARD_H> ScoreBoard;

        Image<I_SAILORMARS_W, I_SAILORMARS_H> SailorMars;
        Image<I_SAILORMERCURY_W, I_SAILORMERCURY_H> SailorMercury;

        Font<I_FANTASQUEFONT_W, I_FANTASQUEFONT_H> FantasqueFont;
        Font<I_SCOREFONT_W, I_SCOREFONT_H> ScoreFont;

        /* Game data */
        Board::t_tile **board;
        char player;

        Referee ref;

        size_t px, py;

        int *scores;
        char mode, piece;

        IAI **ais;
        int ai, nai;

        void UpdateBoard(char mx, char my); // Update the board base on last move played
    public:
        Game();
        virtual ~Game();
        GameState Update(int dtms, void *dataPtr);
        void Draw(void *dataPtr);
};

#endif
