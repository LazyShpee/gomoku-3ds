#ifndef MAINMENU_H_
# define MAINMENU_H_

# include <3ds.h>
# include <stdlib.h>

# include "../include/GameState.hpp"
# include "../include/IFrame.hpp"
# include "../include/Graphics.hpp"

class MainMenu : public IFrame {
    private:
        u32 kDown;

        Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
        Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;

        Font<200, 20> FontTest;
    public:
        MainMenu();
        virtual ~MainMenu();
        GameState Update(int dtms, void *dataPtr);
        void Draw();
};

#endif