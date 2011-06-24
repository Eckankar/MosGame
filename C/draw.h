#ifndef DRAW_H_A6961439
#define DRAW_H_A6961439

#include "general.h"

// The color tags in order. (IMPORTANT TO KEEP THESE IN ASCII-SORTED ORDER)
enum COLORTAGS {
    RGB,
    RGBA
};

// The rectangle tags in order. (IMPORTANT TO KEEP THESE IN ASCII-SORTED ORDER)
enum RECTANGLETAGS {
    FilledRectangle,
    Rectangle
};

// The circle tags in order. (IMPORTANT TO KEEP THESE IN ASCII-SORTED ORDER)
enum CIRCLETAGS {
    Circle,
    FilledCircle
};

// ML type: surface -> point -> color -> unit
// Draws a pixel on the surface.
EXTERNML value draw_draw_pixel(value wScreen, value wPos, value wColor);

// ML type: surface -> point -> point -> color -> bool -> unit
// Draws a line from wStart to wEnd of wColor on wScreen.
// If wAntialias is true, then the line will be antialiased.
EXTERNML value draw_draw_line(value wScreen, value wStart, value wEnd,
                                             value wColor, value wAntiAlias);

// ML type: surface -> rectangle -> color -> unit
// Draws a rectangle of the given color on the surface.
EXTERNML value draw_draw_rectangle(value wScreen, value wRect, value wColor);

// ML type: surface -> circle -> color -> unit
// Draws a circle of the given color on the surface.
EXTERNML value draw_draw_circle(value wScreen, value wCircle, value wColor);
#endif

