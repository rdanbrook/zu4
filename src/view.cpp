#include <SDL.h>

#include "image.h"
#include "imagemgr.h"
#include "settings.h"
#include "view.h"

Image *View::screen = NULL;

View::View(int x, int y, int width, int height)
: x(x), y(y), width(width), height(height), highlighted(false), highlightX(0), highlightY(0), highlightW(0), highlightH(0)
{
    if (screen == NULL)
        screen = xu4_img_get_screen();
}

/**
 * Hook for reinitializing when graphics reloaded.
 */
void View::reinit() {
    screen = xu4_img_get_screen();
}

/**
 * Clear the view to black.
 */
void View::clear() {
    unhighlight();
    xu4_img_fill(screen, x, y, width, height, 0, 0, 0, 255);
}

/**
 * Update the view to the screen.
 */
void View::update() {
    if (highlighted)
        drawHighlighted();
}

/**
 * Update a piece of the view to the screen.
 */
void View::update(int x, int y, int width, int height) {
    if (highlighted)
        drawHighlighted();
}

/**
 * Highlight a piece of the screen by drawing it in inverted colors.
 */ 
void View::highlight(int x, int y, int width, int height) {
    highlighted = true;
    highlightX = x;
    highlightY = y;
    highlightW = width;
    highlightH = height;
    
    update(x, y, width, height);
}

void View::unhighlight() {
    highlighted = false;
    update(highlightX, highlightY, highlightW, highlightH);
    highlightX = highlightY = highlightW = highlightH = 0;
}

void View::drawHighlighted() {
    Image *screen = xu4_img_get_screen();
    
    Image *tmp = xu4_img_create(highlightW, highlightH);
    if (!tmp)
        return;
    
    xu4_img_draw_subrect_on(tmp, screen, 0, 0, this->x + highlightX, this->y + highlightY, highlightW, highlightH);
    xu4_img_draw_highlighted(tmp);
    xu4_img_draw(tmp, (this->x + highlightX), (this->y + highlightY));
    delete tmp;
}
