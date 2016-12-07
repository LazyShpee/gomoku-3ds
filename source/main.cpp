#include <string.h>
#include "graphics.h"
#include "megaman_bgr.h"

int main()
{
	gfxInitDefault();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	Screen<TOP_WIDTH, TOP_HEIGHT, GFX_TOP, GFX_LEFT> TopScreen;
	Screen<BOTTOM_WIDTH, BOTTOM_HEIGHT, GFX_BOTTOM, GFX_LEFT> BottomScreen;
	Image<205, 163> Megaman(megaman_bgr, 0xea00ed);
	int x = 50, y = 50;
	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysHeld();
		if (kDown & KEY_START && kDown & KEY_SELECT)
			break; // break in order to return to hbmenu

		x += !!(kDown & KEY_RIGHT) - !!(kDown & KEY_LEFT);
		y += !!(kDown & KEY_DOWN) - !!(kDown & KEY_UP);

		TopScreen.GetFrameBuffer();
		TopScreen.Fill(0x33FF33);
		TopScreen.SetPixel(10, 10, 0xFF0000);
		TopScreen.SetPixel(20, 10, 255, 0, 0);
		TopScreen.DrawImage(Megaman, x, y);

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
