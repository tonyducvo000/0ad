#ifndef __OGL_H__
#define __OGL_H__


// Enable oglCheck(), which breaks into the debugger whenever
// an OpenGL call fails. (Then insert dozens of calls to oglCheck()
// to locate the cause of the problem.)
#if !( defined(NDEBUG) || defined(TESTING) )
# define OGL_CHECKS
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include "sysdep/win/wgl.h"
#endif


//
// OpenGL header
//

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
#endif


//
// glext
//

// if gl.h provides real prototypes for 1.2 / 1.3 functions,
// exclude the corresponding function pointers in glext_funcs.h
#ifdef GL_VERSION_1_2
#define REAL_GL_1_2
#endif
#ifdef GL_VERSION_1_3
#define REAL_GL_1_3
#endif

#undef GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
# include <OpenGL/glext.h>
#else
# include <GL/glext.h>
# ifdef _WIN32
#  include <GL/wglext.h>
# endif 
#endif

#define GL_TEXTURE_IMAGE_SIZE_ARB 0x86A0


//
// function pointer declarations
//

#ifdef _WIN32
# define CALL_CONV __stdcall
#else
# define CALL_CONV
#endif

#define FUNC(ret, name, params) extern ret (CALL_CONV *name) params;
#define FUNC2(ret, nameARB, nameCore, version, params) extern ret (CALL_CONV *nameARB) params;
#include "glext_funcs.h"
#undef FUNC2
#undef FUNC

// leave CALL_CONV defined for ogl.cpp



//
// OpenGL util
//

extern int max_tex_size;				// [pixels]
extern int tex_units;
extern int max_VAR_elements;			// GF2: 64K; GF3: 1M
extern bool tex_compression_avail;		// S3TC / DXT{1,3,5}
extern int video_mem;					// [MiB]; approximate


// check if the extension <ext> is supported by the OpenGL implementation
extern bool oglHaveExtension(const char* ext);

// check if the OpenGL implementation is at least at <version>.
// (format: "%d.%d" major minor)
extern bool oglHaveVersion(const char* version);

// print all OpenGL errors
extern void oglPrintErrors(void);

#ifdef OGL_CHECKS
extern void oglCheck(void);
#else
# define oglCheck()
#endif

// call before using any of the above, and after each mode change.
//
// fails if OpenGL not ready for use.
extern void oglInit(void);

// set detect.cpp gfx_card[] and gfx_drv_ver[].
// (called by detect.cpp get_gfx_info()).
// 
// fails if OpenGL not ready for use.
// gfx_card and gfx_drv_ver are unchanged on failure.
extern int ogl_get_gfx_info(void);

// return a NULL-terminated string (of unlimited length) containing
// a space-separated list of supported extensions.
extern const char* oglExtList(void);

#ifdef __cplusplus
}
#endif

#endif	// #ifndef __OGL_H__
