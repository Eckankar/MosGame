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
#endif

#ifndef false
#define false 0
#endif

#endif

