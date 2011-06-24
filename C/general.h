#ifndef GENERAL_H_0C741763
#define GENERAL_H_0C741763

#include <stdlib.h>

// SDL includes:
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

// MosML includes:
#include <mlvalues.h>		/* For Val_unit, Long_val, String_val, ... */
#include <alloc.h>		/* For copy_string, alloc_string, ...      */
#include <memory.h>		/* For Modify, Push_roots, Pop_roots       */
//#include <str.h>		/* For string_length                       */
#include <fail.h>		/* For failwith                            */

// Export for ML
#ifdef WIN32
#define EXTERNML __declspec(dllexport)
#else
#define EXTERNML
#endif

#ifndef true
#define true 1
#define false 0
#endif

// Define useful things related to ML lists
#ifndef Nil_tag
#define Nil_tag 0
#define Cons_tag 1
#define Val_nil Atom(0)
#endif

// SDL doesn't define a SDL_NOEVENTS, so let's do this instead:
#ifndef SDL_NOEVENTS
#define SDL_NOEVENTS (SDL_ALLEVENTS ^ SDL_ALLEVENTS)
#endif

#endif

