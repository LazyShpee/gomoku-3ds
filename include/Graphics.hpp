#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include <iostream>
# include <string.h>
# include <vector>
# include <3ds.h>
# include <string>
# include <assert.h>
# include "Assets.hpp"

# define TOP_HEIGHT         240 // Top screen height
# define TOP_WIDTH          400 // Top screen width
# define TOP_SIZE           (TOP_HEIGHT * TOP_WIDTH)

# define BOTTOM_HEIGHT      240 // Bottom screen height
# define BOTTOM_WIDTH       320 // Bottom screen width
# define BOTTOM_SIZE           (BOTTOM_HEIGHT * BOTTOM_WIDTH)

# define C_WHITE    0xFFFFFF
# define C_RED      0xFF0000
# define C_GREEN    0x00FF00
# define C_BLUE     0x0000FF
# define C_BLACK    0x000000
# define C_ALPHA    0xFF1CCC

# define RGB_TO_I(r, g, b) (r << 16 | g << 8 | b)
# define I_TO_R(i) ((i & 0xFF << 16) >> 16)
# define I_TO_G(i) ((i & 0xFF << 8) >> 8)
# define I_TO_B(i) ((i & 0xFF))

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
            if (!this->fb || x >= WIDTH || y >= HEIGHT) return (-1);
            size_t offset = 3 * ((HEIGHT - y - 1) + x * HEIGHT);
            int col = this->fb[offset] << 0 |
                    this->fb[offset + 1] << 8 |
                    this->fb[offset + 2] << 16;
            return (col == this->alpha ? -1 : col);
        }

        int GetWidth() const { return WIDTH; }
        int GetHeight() const { return HEIGHT; }
};

typedef struct {
    size_t x;
    size_t y;
    size_t w;
    size_t h;
    char l;
} Letter;

template<size_t WIDTH, size_t HEIGHT>
class Font : public Image<WIDTH, HEIGHT> {
    protected:
        char *charset;
        size_t lencharset;
        int sep;
        std::vector<Letter> letters;
    public:
        Font(const u8 *newfb, std::string const & _charset, int alpha = -1) : Image<WIDTH, HEIGHT>(newfb, alpha), charset(strdup(_charset.c_str())), lencharset(strlen(charset)) {
            sep =   this->fb[0] << 0 |
                    this->fb[1] << 8 |
                    this->fb[2] << 16;
            Letter let = {0, 0, 0, HEIGHT};
            for (size_t x = 1; x < WIDTH; x++) {
                while(x < WIDTH && this->GetPixel(x, 0) == sep) x++;
                let.x = x;
                while(x < WIDTH && this->GetPixel(x, 0) != sep) x++;
                let.w = x - let.x;
                if (x <= WIDTH)
                    letters.push_back(let);
            }
        }
        ~Font() {
            delete this->charset;
        };

        void GetLetter(char letter, Letter *retLetter) {
            size_t i;
            for (i = 0; charset[i]; i++) {
                if (charset[i] == letter) break;
            }
            memcpy(retLetter, &(letters[i]), sizeof(Letter));
        }
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
            size_t offset = 3 * ((HEIGHT - y - 1) + x * HEIGHT);
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
        void DrawImage(Image<W, H> & img, size_t x, size_t y, size_t ix = 0, size_t iy = 0, size_t iw = 0, size_t ih = 0, int recolor = -1) {
            int col;
            if (!iw) iw = img.GetWidth() - ix;
            if (!ih) ih = img.GetHeight() - iy;
            for (size_t cx = ix; cx < ix + iw; cx++) {
                for (size_t cy = iy; cy < iy + ih; cy++) {
                    col = img.GetPixel(cx, cy);
                    if (col >= 0) {
                        if (recolor >= 0)
                            col = RGB_TO_I((I_TO_R(recolor)+I_TO_R(col))/2, (I_TO_G(recolor)+I_TO_G(col))/2, (I_TO_B(recolor)+I_TO_B(col))/2);
                        this->SetPixel(x + cx - ix, y + cy - iy, col);
                    }
                }
            }
        }

        template<size_t W, size_t H>
        void DrawText(Font<W, H> & font, size_t x, size_t y, std::string text, size_t spacing = 0, int recolor = -1) {
            const char *s = text.c_str();
            size_t cx = x, cy = y;
            Letter let;
            for (size_t i = 0; s[i]; i++) {
                font.GetLetter(s[i], &let);
                this->DrawImage(font, cx, cy, let.x, let.y, let.w, let.h, recolor);
                cx += let.w + spacing;
            }
        }
};

#endif // !GRAPHICS_H_