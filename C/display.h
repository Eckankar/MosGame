#ifndef DISPLAY_H_32473B0D
#define DISPLAY_H_32473B0D

#include "general.h"

// ML type: dimensions -> surface
// Creates a new display of the given dimensions.
EXTERNML value display_create_display(value wDimensions);

// ML type: surface -> unit
// Switches the double-buffers.
EXTERNML value display_flip(value wScreen);

// ML type: string -> unit
// Sets the caption of the current window.
EXTERNML value display_set_caption(value wCaption);

// ML type: unit -> string
// Gets the caption of the current window.
EXTERNML value display_get_caption(value null);
#endif

