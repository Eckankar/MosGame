#include "general.h"
#include "surface.h"
#include "draw.h" // for colors

// Converts the ML type 'area' to an SDL_Rect.
void populate_rect (SDL_Rect *rect, value wArea, SDL_Surface *surface) {
    if (Tag_val(wArea) == Full) {
        rect->x = 0;
        rect->y = 0;
        rect->w = surface->w;
        rect->h = surface->h;
    } else {
        rect->x = Long_val(Field(Field(wArea, 0), 0));
        rect->y = Long_val(Field(Field(wArea, 0), 1));
        rect->w = Long_val(Field(Field(wArea, 1), 0));
        rect->h = Long_val(Field(Field(wArea, 1), 1));
    }
}

// ML type: surface -> area -> color -> unit
// Fills the entire surface with the given color.
EXTERNML value surface_fill(value wSurface, value wArea, value wColor) {
    SDL_Surface *screen = (SDL_Surface *)Addr_val(wSurface);

    int colorr = Long_val(Field(wColor, 0)),
        colorg = Long_val(Field(wColor, 1)),
        colorb = Long_val(Field(wColor, 2)),
        colora = Tag_val(wColor) == RGBA ? Long_val(Field(wColor, 3)) : 255;

    Uint32 rgba = SDL_MapRGBA(screen->format, colorr, colorg, colorb, colora);

    SDL_Rect rect;
    populate_rect(&rect, wArea, screen);

    SDL_FillRect(screen, &rect, rgba);

    return Val_unit;
}

// ML type: surface -> area -> surface -> point -> unit
// Draws the contents of wSource onto wTarget, with top left corner
// in wTopLeft
EXTERNML value surface_blit(value wSource, value wArea,
                            value wTarget, value wTopLeft) {
    SDL_Surface *source = (SDL_Surface *)Addr_val(wSource),
                *target = (SDL_Surface *)Addr_val(wTarget);

    SDL_Rect srcRect, tgtRect;

    populate_rect(&srcRect, wArea, source),

    tgtRect.x = Long_val(Field(wTopLeft, 0)),
    tgtRect.y = Long_val(Field(wTopLeft, 1));

    SDL_BlitSurface(source, &srcRect, target, &tgtRect);

    return Val_unit;
}
