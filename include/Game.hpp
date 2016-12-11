#ifndef GAME_H_
# define GAME_H_

# include <3ds.h>
# include <stdlib.h>

# include "../include/GameState.hpp"
# include "../include/IFrame.hpp"
# include "../include/Graphics.hpp"
# include "../include/Referee.hpp"
# include "../include/Board.hpp"

#define BX 65 // Board Start X position
#define BY 25 // Board Start Y position

class Game : public IFrame {
    protected:
        /* Inputs */
        u32 kDown;
        u32 kUp;
        u32 kHeld;
        touchPosition tPos;

        /* Screens */
        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
        Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;

        /* Images */
        Image<I_TOPBG_W, I_TOPBG_H> TopBg;
    	Image<I_BOTTOMBG_W, I_BOTTOMBG_H> BottomBg;
	    Image<I_SPRITES_W, I_SPRITES_H> Sprites;
	    Image<I_GOBAN_W, I_GOBAN_H> Goban;

        Font<I_FANTASQUEFONT_W, I_FANTASQUEFONT_H> FantasqueFont;

        /* Game data */
        Board::t_tile **board;
        char player;
        char lastX;
        char lastY;

        //Referee ref;

        size_t px, py;

        void UpdateBoard(char mx, char my); // Update the board base on last move played
    public:
        Game();
        virtual ~Game();
        GameState Update(int dtms, void *dataPtr);
        void Draw(void *dataPtr);
};

#endif