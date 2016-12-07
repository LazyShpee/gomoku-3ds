#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include <stddef.h>
# include <3ds.h>

# define TOP_HEIGHT         240 // Top screen height
# define TOP_WIDTH          400 // Top screen width
# define TOP_SIZE           (TOP_HEIGHT * TOP_WIDTH)

# define BOTTOM_HEIGHT      240 // Bottom screen height
# define BOTTOM_WIDTH       320 // Bottom screen width
# define BOTTOM_SIZE           (BOTTOM_HEIGHT * BOTTOM_WIDTH)

template<size_t WIDTH, size_t HEIGHT>
class Image {
    protected:
        u8 *fb;
        int alpha;
    public:
        Image(const u8 *newfb, int alpha = -1) : alpha(alpha) {
            this->fb = (u8 *)newfb;
        }

        int GetPixel(size_t x, size_t y) {
            if (!this->fb || x > WIDTH || y > HEIGHT) return (-1);
            size_t offset = 3 * ((HEIGHT - y) + x * HEIGHT);
            int col = this->fb[offset] << 0 |
                    this->fb[offset + 1] << 8 |
                    this->fb[offset + 2] << 16;
            return (col == this->alpha ? -1 : col);
        }

        int GetWidth() const { return WIDTH; }
        int GetHeight() const { return HEIGHT; }
};

template<size_t WIDTH, size_t HEIGHT, gfxScreen_t SCREEN, gfx3dSide_t SIDE>
class Screen : public Image<WIDTH, HEIGHT> {
    public:
        Screen() : Image<WIDTH, HEIGHT>(NULL) {}
        ~Screen() {}

        void GetFrameBuffer() {
            this->fb = gfxGetFramebuffer(SCREEN, SIDE, NULL, NULL);
        }

        void SetPixel(size_t x, size_t y, int color) {
            if (!this->fb || x >= WIDTH || y >= HEIGHT) return;
            char rgb[4];
            memcpy(rgb, &color, 3);
            SetPixel(x, y, rgb[2], rgb[1], rgb[0]);
        }

        void SetPixel(size_t x, size_t y, char r, char g, char b) {
            if (!this->fb || x >= WIDTH || y >= HEIGHT) return;
            size_t offset = 3 * ((HEIGHT - y) + x * HEIGHT);
            this->fb[offset] = b;
            this->fb[offset + 1] = g;
            this->fb[offset + 2] = r;
        }

        void Fill(int color) {
            for (size_t x = 0; x < WIDTH; x++) {
                for (size_t y = 0; y < HEIGHT; y++) {
                    this->SetPixel(x, y, color);
                }
            }
        }

        void Fill(char r, char g, char b) {
            for (size_t x = 0; x < WIDTH; x++) {
                for (size_t y = 0; y < HEIGHT; y++) {
                    this->SetPixel(x, y, r, g, b);
                }
            }
        }

        template<size_t W, size_t H>
        void DrawImage(Image<W, H> & img, size_t x, size_t y, size_t ix = 0, size_t iy = 0, size_t iw = 0, size_t ih = 0) {
            int col;
            if (!iw) iw = img.GetWidth() - ix;
            if (!ih) ih = img.GetHeight() - iy;
            for (size_t cx = ix; cx < ix + iw; cx++) {
                for (size_t cy = iy; cy < iy + ih; cy++) {
                    col = img.GetPixel(cx, cy);
                    if (col >= 0)
                        this->SetPixel(x + cx - ix, y + cy - iy, col);
                }
            }
        }
};

#endif // !GRAPHICS_H_