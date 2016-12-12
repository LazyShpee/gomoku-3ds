#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "../include/Images.hpp"
#include "../include/Game.hpp"
#include "../include/GameOver.hpp"
#include "../include/MainMenu.hpp"
int main(int ac, char **av, char **env)
{
	GameState retState;
	struct timeval timeNow;
	int timeThen;
	gettimeofday(&timeNow, NULL);
	int dtms;

	srand(time(NULL));
	gfxInitDefault();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	GameOver * gameover = new GameOver;
	Game * game = new Game;
	MainMenu * menu = new MainMenu;
	IFrame * currentFrame = menu;
	int dataPtr = 0;

	while (aptMainLoop())
	{
		gspWaitForVBlank(); // Wait for next frame
		hidScanInput(); // Read inputs

		timeThen = timeNow.tv_sec * 1000000 + timeNow.tv_usec;
		gettimeofday(&timeNow, NULL);
		dtms = timeNow.tv_sec * 1000000 + timeNow.tv_usec - timeThen; // Calc time in ms since last update

		retState = currentFrame->Update(dtms, (void *)&dataPtr); // Update current frame

		if (retState == ST_NEWGAME) {
			delete game;
			game = new Game;
			currentFrame = game;
		} else if (retState == ST_GAMEOVER) {
			delete gameover;
			gameover = new GameOver;
			currentFrame = gameover;
		} else if (retState == ST_MENU) currentFrame = menu;
		else if (retState == ST_RESUME) currentFrame = game;
		else if (retState == ST_QUIT) break;

		currentFrame->Draw((void *)&dataPtr); // Draw current frame

		gfxFlushBuffers(); // Clear currently displayed frame buffer
		gfxSwapBuffers(); // Swap frame buffer
	}
	if (game) delete game;
	if (gameover) delete gameover;

	gfxExit();
	return 0;
}
