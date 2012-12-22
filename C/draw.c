#include "general.h"
#include "draw.h"
#include "util.h"

// ML type: surface -> point -> point -> color -> bool -> unit
// Draws a line from wStart to wEnd of wColor on wScreen.
// If wAntialias is true, then the line will be antialiased.
EXTERNML value draw_draw_line(value wScreen, value wStart, value wEnd,
                                             value wColor, value wAntiAlias) {
    SDL_Surface *screen = (SDL_Surface *)Addr_val(wScreen);

    int startx = Long_val(Field(wStart, 0)),
        starty = Long_val(Field(wStart, 1)),
        endx   = Long_val(Field(wEnd, 0)),
        endy   = Long_val(Field(wEnd, 1)),
        colorr = Long_val(Field(wColor, 0)),
        colorg = Long_val(Field(wColor, 1)),
        colorb = Long_val(Field(wColor, 2)),
        colora = Tag_val(wColor) == RGBA ? Long_val(Field(wColor, 3)) : 255;

    if (colorr < 0 || colorr > 255 ||
        colorg < 0 || colorg > 255 ||
        colorb < 0 || colorb > 255 ||
        colora < 0 || colora > 255) {
        invalid_argument("Invalid color value given - each value must be between 0 and 255.");
    }

    if (Bool_val(wAntiAlias)) {
        aalineRGBA(screen, startx, starty, endx, endy, colorr, colorg, colorb, 255);
    } else {
        lineRGBA(screen, startx, starty, endx, endy, colorr, colorg, colorb, 255);
    }

    return Val_unit;
}

// ML type: surface -> point -> color -> unit
// Draws a pixel on the surface.
EXTERNML value draw_draw_pixel(value wScreen, value wPos, value wColor) {
    SDL_Surface *screen = (SDL_Surface *)Addr_val(wScreen);

    int x = Long_val(Field(wPos, 0)),
        y = Long_val(Field(wPos, 1)),
        colorr = Long_val(Field(wColor, 0)),
        colorg = Long_val(Field(wColor, 1)),
        colorb = Long_val(Field(wColor, 2)),
        colora = Tag_val(wColor) == RGBA ? Long_val(Field(wColor, 3)) : 255;

    pixelRGBA(screen, x, y, colorr, colorg, colorb, colora);

    return Val_unit;
}

// ML type: surface -> rectangle -> color -> unit
// Draws a rectangle of the given color on the surface.
EXTERNML value draw_draw_rectangle(value wScreen, value wRect, value wColor) {
    SDL_Surface *screen = (SDL_Surface *)Addr_val(wScreen);

    int x = Long_val(Field(Field(wRect, 0), 0)),
        y = Long_val(Field(Field(wRect, 0), 1)),
        w = Long_val(Field(Field(wRect, 1), 0)),
        h = Long_val(Field(Field(wRect, 1), 1)),
        colorr = Long_val(Field(wColor, 0)),
        colorg = Long_val(Field(wColor, 1)),
        colorb = Long_val(Field(wColor, 2)),
        colora = Tag_val(wColor) == RGBA ? Long_val(Field(wColor, 3)) : 255;

    if (Tag_val(wRect) == FilledRectangle) {
        boxRGBA(screen, x, y, x+w, y+h, colorr, colorg, colorb, colora);
    } else {
        rectangleRGBA(screen, x, y, x+w, y+h,
                              colorr, colorg, colorb, colora);
    }

    return Val_unit;
}

// ML type: surface -> circle -> color -> unit
// Draws a circle of the given color on the surface.
EXTERNML value draw_draw_circle(value wScreen, value wCircle, value wColor) {
    SDL_Surface *screen = (SDL_Surface *)Addr_val(wScreen);

    int x = Long_val(Field(Field(wCircle, 0), 0)),
        y = Long_val(Field(Field(wCircle, 0), 1)),
        r = Long_val(Field(wCircle, 1)),
        colorr = Long_val(Field(wColor, 0)),
        colorg = Long_val(Field(wColor, 1)),
        colorb = Long_val(Field(wColor, 2)),
        colora = Tag_val(wColor) == RGBA ? Long_val(Field(wColor, 3)) : 255;

    if (Tag_val(wCircle) == FilledCircle) {
        filledCircleRGBA(screen, x, y, r, colorr, colorg, colorb, colora);
    } else if (Tag_val(wCircle) == AntiAliasedCircle) {
        aacircleRGBA(screen, x, y, r, colorr, colorg, colorb, colora);
    } else {
        circleRGBA(screen, x, y, r, colorr, colorg, colorb, colora);
    }

    return Val_unit;
}
