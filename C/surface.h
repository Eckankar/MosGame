#ifndef SURFACE_H_65529D67
#define SURFACE_H_65529D67

#include "general.h"

enum AREA {
    Full,
    Partial
};

// ML type: surface -> color -> area -> unit
// Fills the given area surface with the given color.
EXTERNML value surface_fill(value wScreen, value wArea, value wColor);

// ML type: surface -> area -> surface -> point -> unit
// Draws the contents of wArea on wSource onto wTarget,
// with top left corner in wTopLeft.
EXTERNML value surface_blit(value wSource, value wArea,
                            value wTarget, value wTopLeft);
#endif

