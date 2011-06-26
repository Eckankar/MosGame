#include "general.h"
#include "surface.h"
#include "draw.h" // for colors

// ML type: surface -> color -> unit
// Fills the entire surface with the given color.
EXTERNML value surface_fill(value wScreen, value wColor) {
    SDL_Surface *screen = Addr_val(wScreen);

    int colorr = Long_val(Field(wColor, 0)),
        colorg = Long_val(Field(wColor, 1)),
        colorb = Long_val(Field(wColor, 2)),
        colora = Tag_val(wColor) == RGBA ? Long_val(Field(wColor, 3)) : 255;

    Uint32 rgba = SDL_MapRGBA(screen->format, colorr, colorg, colorb, colora);

    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = screen->w;
    rect.h = screen->h;

    SDL_FillRect(screen, &rect, rgba);

    return Val_unit;
}
