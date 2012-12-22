#include "general.h"
#include "mosgame.h"

// ML type: unit -> unit
EXTERNML value mosgame_init(value null) {
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        char err[512];
        snprintf(err, 512, "Unable to init SDL: %s\n", SDL_GetError());
        failwith(err);
    }

    return Val_unit;
}

// ML type: unit -> unit
EXTERNML value mosgame_quit(value null) {
    SDL_Quit();

    return Val_unit;
}
