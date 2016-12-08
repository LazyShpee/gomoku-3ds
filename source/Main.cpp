#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "../include/Game.hpp"
#include "../include/MainMenu.hpp"
int main()
{
	GameState retState;
	struct timeval timeNow;
	int timeThen;
	gettimeofday(&timeNow, NULL);
	int dtms;

	srand(time(NULL));
	gfxInitDefault();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	Game * game = new Game;
	MainMenu * menu = new MainMenu;
	IFrame * currentFrame = menu;
	int dataPtr;

	while (aptMainLoop())
	{
		gspWaitForVBlank(); // Wait for next frame
		hidScanInput(); // Read inputs

		timeThen = timeNow.tv_sec * 1000 + timeNow.tv_usec / 1000;
		gettimeofday(&timeNow, NULL);
		dtms = timeNow.tv_sec * 1000 + timeNow.tv_usec  / 1000 - timeThen; // Calc time in ms since last update

		retState = currentFrame->Update(dtms, (void *)&dataPtr); // Update current frame

		if (retState == ST_NEWGAME) {
			delete game;
			game = new Game;
		} else if (retState == ST_QUIT) {
			break;
		}

		currentFrame->Draw(); // Draw current frame

		gfxFlushBuffers(); // Clear currently displayed frame buffer
		gfxSwapBuffers(); // Swap frame buffer
	}
	if (game) delete game;


	gfxExit();
	return 0;
}
