#include "general.h"
#include "image.h"
#include "util.h"

#include <SDL_image.h>

// ML type: string -> surface
// Loads the image at the given filename into a surface.
EXTERNML value image_load(value wFilename) {
    SDL_Surface *surface = IMG_Load( String_val(wFilename) );

    if (surface == NULL) {
        failwith(IMG_GetError());
    }

    return Val_addr(surface);
}

// ML type: surface -> string -> unit
// Saves the surface to an image file.
EXTERNML value image_save(value wSurface, value wFilename) {
    SDL_Surface *surface = Addr_val(wSurface);

    SDL_SaveBMP(surface, String_val(wFilename));

    return Val_unit;
}
