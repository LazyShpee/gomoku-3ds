#ifndef GAME_H_
# define GAME_H_

# include <3ds.h>
# include <stdlib.h>

# include "../include/GameState.hpp"
# include "../include/IFrame.hpp"
# include "../include/Graphics.hpp"

#define BX 65 // Board Start X position
#define BY 25 // Board Start Y position

class Game : public IFrame {
    protected:
        /* Inputs */
        u32 kDown;
        u32 kUp;
        u32 kHeld;
        touchPosition posTouch;

        /* Screens */
        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
        Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;

        /* Images */
        Image<400, 240> TopBg;
	    Image<100, 100> Sprites;
    	Image<320, 240> BottomBg;

        /* Game data */
        char board[19][19];
        char player;
        char lastX;
        char lastY;

        void UpdateBoard(char mx, char my); // Update the board base on last move played
    public:
        Game();
        virtual ~Game();
        GameState Update(int dtms, void *dataPtr);
        void Draw();
};

#endif