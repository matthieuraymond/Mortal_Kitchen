#pragma once

#define LIBSL_VERSION_MAJOR 1
#define LIBSL_VERSION_MINOR 2

//#pragma message("Including LibSL.config.h")

/* #undef USE_GLUX */
#define LIBSL_BUILD_MAX_PERFORMANCE

#ifdef LIBSL_BUILD_MAX_PERFORMANCE
#define LIBSL_RELEASE
#endif

