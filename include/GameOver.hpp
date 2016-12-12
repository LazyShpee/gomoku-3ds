#ifndef GAMEOVER_H_
# define GAMEOVER_H_

# include "../include/IFrame.hpp"
# include "../include/Graphics.hpp"

class GameOver : public IFrame {
    private:
        u32 kDown;

        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
        Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;

        Image<I_TOPBG_W, I_TOPBG_H> TopBg;
    	Image<I_BOTTOMBG_W, I_BOTTOMBG_H> BottomBg;

    public:
        GameOver();
        virtual ~GameOver();
        GameState Update(int dtms, void *dataPtr);
        void Draw(void *dataPtr);
};

#endif