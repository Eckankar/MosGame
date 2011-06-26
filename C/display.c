#include <string.h> // for strlen

#include "general.h"
#include "util.h"
#include "display.h"
#include "draw.h"

// ML type: dimensions -> surface
EXTERNML value display_create_display(value wDimensions) {
    int width = Int_val(Field(wDimensions, 0));
    int height = Int_val(Field(wDimensions, 1));

    // create a new window
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (!screen) {
        char err[512];
        snprintf(err, 512, "Unable to set %dx%d video: %s\n", width, height, SDL_GetError());
        failwith(err);
    }

    return Val_addr(screen);
}

// ML type: surface -> unit
// Switches the double-buffers.
EXTERNML value display_flip(value wScreen) {
    SDL_Surface *screen = Addr_val(wScreen);

    SDL_Flip(screen);

    return Val_unit;
}

// ML type: string -> unit
// Sets the caption of the current window
EXTERNML value display_set_caption(value wCaption) {
    char *caption = String_val(wCaption);

    SDL_WM_SetCaption(caption, caption);

    return Val_unit;
}

// ML type: unit -> string
// Gets the caption of the current window
EXTERNML value display_get_caption(value null) {
    char *caption, *icon;

    SDL_WM_GetCaption(&caption, &icon);

    char *emptystring = "";
    if (caption == NULL) {
        caption = emptystring;
    }

    int size = strlen(caption);

    value res = alloc_string(size);
    memcpy(String_val(res), caption, size+1);

    return res;
}
