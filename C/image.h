#ifndef IMAGE_H_F6AFF1DB
#define IMAGE_H_F6AFF1DB

#include "general.h"

// ML type: string -> surface
// Loads the image at the given filename into a surface.
EXTERNML value image_load(value wFilename);

// ML type: surface -> string -> unit
// Saves the surface to an image file.
EXTERNML value image_save(value wSurface, value wFilename);

#endif

