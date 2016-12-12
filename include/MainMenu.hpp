#ifndef MAINMENU_H_
# define MAINMENU_H_

# include <3ds.h>
# include <stdlib.h>

# include "../include/GameState.hpp"
# include "../include/IFrame.hpp"
# include "../include/Graphics.hpp"

# define BTN_COLLIDE(x, y, cx, cy) (cx > x && cx < x + I_BUTTONBACK_W && cy > y && cy < y + I_BUTTONBACK_H)

class MainMenu : public IFrame {
    private:
        u32 kDown;
        u32 kHeld;
        touchPosition tPos;

        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
        Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;

        Image<I_TOPBG_W, I_TOPBG_H> TopBg;
    	Image<I_BOTTOMBG_W, I_BOTTOMBG_H> BottomBg;

        Image<I_SAILORMARS_W, I_SAILORMARS_H> SailorMars;
        Image<I_SAILORMERCURY_W, I_SAILORMERCURY_H> SailorMercury;
        Image<I_TITLE_W, I_TITLE_H> Title;

        Image<I_BUTTONBACK_W, I_BUTTONBACK_H> ButtonBack;

        Font<I_FANTASQUEFONT_W, I_FANTASQUEFONT_H> FantasqueFont;

        int Ma_x, Me_x, Title_y;
        int timer;

        enum GameModes {
            PVP = 0,
            PVI = 1,
            IVI = 2
        };

        GameModes GameMode;

    public:
        MainMenu();
        virtual ~MainMenu();
        GameState Update(int dtms, void *dataPtr);
        void Draw(void *dataPtr);
};

#endif