/*
 * $Id: image.h 3032 2012-05-18 19:39:47Z twschulz $
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <stdint.h>
#include <SDL.h> // very very temporary
#include "types.h"
#include "u4file.h"
#include "textcolor.h"

struct SDL_Surface;

using std::string;

typedef struct RGBA {
    unsigned int r, g, b, a;
} RGBA;

#define DARK_GRAY_HALO (RGBA){14,15,16,255}

typedef struct SubImage {
    string name;
    string srcImageName;
    int x, y, width, height;
} SubImage;

#define IM_OPAQUE (unsigned int) 255
#define IM_TRANSPARENT 0

class Image {
public:
    static Image *create(int w, int h);
    static Image *createScreenImage();
    static Image *duplicate(Image *image);
    ~Image();

    /* alpha handling */
    bool isAlphaOn() const;
    void alphaOn();
    void alphaOff();

    /* Will clear the image to the background color, and set the internal backgroundColor variable */
    void initializeToBackgroundColor(RGBA backgroundColor = DARK_GRAY_HALO);

    uint32_t getPixel(int x, int y);
    void putPixel(int x, int y, uint32_t value);
    void fillRect(int x, int y, int w, int h, int r, int g, int b, int a=IM_OPAQUE);

    /**
     * Draws the entire image onto the screen at the given offset.
     */
    void draw(int x, int y) const {
        drawOn(NULL, x, y);
    }

    /**
     * Draws a piece of the image onto the screen at the given offset.
     * The area of the image to draw is defined by the rectangle rx, ry,
     * rw, rh.
     */
    void drawSubRect(int x, int y, int rx, int ry, int rw, int rh) const {
        drawSubRectOn(NULL, x, y, rx, ry, rw, rh);
    }

    /**
     * Draws a piece of the image onto the screen at the given offset, inverted.
     * The area of the image to draw is defined by the rectangle rx, ry,
     * rw, rh.
     */
    void drawSubRectInverted(int x, int y, int rx, int ry, int rw, int rh) const {
        drawSubRectInvertedOn(NULL, x, y, rx, ry, rw, rh);
    }

    /* image drawing methods for drawing onto another image instead of the screen */
    void drawOn(Image *d, int x, int y) const;
    void drawSubRectOn(Image *d, int x, int y, int rx, int ry, int rw, int rh) const;
    void drawSubRectInvertedOn(Image *d, int x, int y, int rx, int ry, int rw, int rh) const;

    unsigned int w, h;
    RGBA backgroundColor;
    SDL_Surface *surface;
};

#endif /* IMAGE_H */
