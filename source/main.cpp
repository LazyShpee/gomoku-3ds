#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/GameState.hpp"
#include "../include/Game.hpp"

int main()
{
	GameState retState;

	srand(time(NULL));
	gfxInitDefault();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	// Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
	// Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;
	// Main loop

	Game * game = new Game;
	IFrame * currentFrame = game;

	while (aptMainLoop())
	{
		gspWaitForVBlank(); // Wait for next frame
		hidScanInput(); // Read inputs

		retState = currentFrame->Update(16); // Update current frame
		if (retState == ST_RESET) {
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
