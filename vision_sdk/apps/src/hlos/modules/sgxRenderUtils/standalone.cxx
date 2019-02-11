/*
 Copyright (c) Texas Instruments Incorporated
*/

/*******************************************************************************************************************************************
 Include Files
*******************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(PLATFORM_GLFW)
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#elif defined(PLATFORM_EGL)
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#elif defined(PLATFORM_GLX)
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include <GL/glx.h>
#else
#error "Must define PLATFORM_GLFW, PLATFORM_EGL or PLATFORM_GLX"
#endif


#include "render.h"

#include "standalone/BoxLUT.c"

#ifndef DYNAMIC_LUT
#include "standalone/GAlignLUT.c"
#endif

FILE *outfile;
FILE *coutfile;
int srv_select = 3;
int srv_car = 1;
int srv_bowl = 1;
int srv_view = 2;
char *out_filename;

int readx = 585;
int ready = 49;
int readwidth = 752;
int readheight = 1008;
int subsample = 8;//2^3: Sub sampling while writing output file
//static GC gc;
extern int srv_param_select;
extern bool srv_param_car;
extern bool srv_param_bowl;
extern int srv_param_view1;
extern int srv_param_view2;
extern int srv_param_step;
extern bool srv_render_to_file;
extern int num_iterations;
extern bool srv_exit;

render_state_t render3DSRVObj;

typedef struct {
	float x, y, z;
} worldcoords;

/*******************************************************************************************************************************************
 Defines
*******************************************************************************************************************************************/
// Name of the application
#define APPLICATION_NAME "Standalone 3DSRV"

// Width and height of the window
#define WINDOW_WIDTH	1920
#define WINDOW_HEIGHT	1080
/*******************************************************************************************************************************************
 Helper Functions
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
 Application Functions
*******************************************************************************************************************************************/

int load_texture_from_raw_file(GLuint tex, int width, int height, int textureType,  const char* filename, int offset);
int load_texture_bmp(GLuint tex, const char *filename);
void get_bmp_info(const char *filename, uint32_t *width, uint32_t *height, uint32_t *bpp);

#ifdef PLATFORM_GLFW
GLFWwindow* window;
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int setup_gl_context()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(1920, 1080, "Test Window", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}
	return 0;
}

void terminate_gl_context()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void swap_buffers()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
#endif

#ifdef PLATFORM_EGL
EGLDisplay			eglDisplay = NULL;
EGLConfig			eglConfig = NULL;
EGLSurface			eglSurface = NULL;
EGLContext			eglContext = NULL;

bool TestEGLError(const char* functionLastCalled)
{
	EGLint lastError = eglGetError();
	if (lastError != EGL_SUCCESS)
	{
		printf("%s failed (%x).\n", functionLastCalled, lastError);
		return false;
	}
	return true;
}

bool TestGLError(const char* functionLastCalled)
{
	GLenum lastError = glGetError();
	if (lastError != GL_NO_ERROR)
	{
		printf("%s failed (%x).\n", functionLastCalled, lastError);
		return false;
	}

	return true;
}

int setup_gl_context()
{
	int err = -1;
	EGLint eglMajorVersion, eglMinorVersion;
	EGLint configsReturned;
	const EGLint configurationAttributes[] =
	{
		EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};
	EGLint contextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	eglDisplay = eglGetDisplay((EGLNativeDisplayType)0);
	if (eglDisplay == EGL_NO_DISPLAY)
	{
		printf("Failed to get an EGLDisplay");
		err = -1;
		goto error_eglGetDisplay;
	}

	if (!eglInitialize(eglDisplay, &eglMajorVersion, &eglMinorVersion))
	{
		printf("Failed to initialise the EGLDisplay");
		err = -1;
		goto error_eglInitialize;
	}
	if (!eglChooseConfig(eglDisplay, configurationAttributes, &eglConfig, 1, &configsReturned) || (configsReturned != 1))
	{
		printf("Failed to choose a suitable config.");
		err = -1;
		goto error_eglChooseConfig;
	}

	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)0, NULL);
	if (!TestEGLError("eglCreateWindowSurface"))
	{
		err = -1;
		goto error_eglCreateWindowSurface;
	}

	eglBindAPI(EGL_OPENGL_ES_API);
	if (!TestEGLError("eglBindAPI"))
	{
		err = -1;
		goto error_eglBindAPI;
	}

	// Create the context with the context attributes supplied
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, contextAttributes);
	if (!TestEGLError("eglCreateContext"))
	{
		err = -1;
		goto error_eglCreateContext;
	}

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (!TestEGLError("eglMakeCurrent"))
	{
		err = -1;
		goto error_eglMakeCurrent;
	}

	err = 0;
	return err;

error_eglMakeCurrent:
	eglDestroyContext(eglDisplay, eglContext);
error_eglCreateContext:
error_eglBindAPI:
	eglDestroySurface(eglDisplay, eglSurface);
error_eglCreateWindowSurface:
error_eglChooseConfig:
	eglTerminate(eglDisplay);
error_eglInitialize:
error_eglGetDisplay:
	return err;
}

void terminate_gl_context()
{
	if(eglDisplay != NULL)
	{
		eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(eglDisplay, eglContext);
		eglDestroySurface(eglDisplay, eglSurface);
		eglTerminate(eglDisplay);
	}
}

void swap_buffers()
{
	eglSwapBuffers(eglDisplay, eglSurface);
}
#endif

#ifdef PLATFORM_GLX
#define GLX_CONTEXT_MAJOR_VERSION_ARB		0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB		0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

static GLXContext ctx;
static XVisualInfo *vi;
static GC gc;
// X11 variables
Display* display;
Window win;
Pixmap pm;
GLXPixmap glxpm;

static bool isExtensionSupported(const char *extList, const char *extension)
{
  const char *start;
  const char *where, *terminator;

  /* Extension names should not have spaces. */
  where = strchr(extension, ' ');
  if (where || *extension == '\0')
    return false;

  /* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings,
     etc. */
  for (start=extList;;) {
    where = strstr(start, extension);

    if (!where)
      break;

    terminator = where + strlen(extension);

    if ( where == start || *(where - 1) == ' ' )
      if ( *terminator == ' ' || *terminator == '\0' )
        return true;

    start = terminator;
  }

  return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    ctxErrorOccurred = true;
    return 0;
}

static Window create_window(Display *display, unsigned int width, unsigned int height)
{
	int drawable_type;
	int double_buffer_enable;

	if(srv_render_to_file == true)
	{
		drawable_type = GLX_PIXMAP_BIT;
		double_buffer_enable = False;
	}
	else
	{
		drawable_type = GLX_WINDOW_BIT;
		double_buffer_enable = True;
	}
	// Get a matching FB config
	static int visual_attribs[] =
	{
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , drawable_type,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , double_buffer_enable,
		//GLX_SAMPLE_BUFFERS  , 1,
		//GLX_SAMPLES         , 4,
		None
	};

	int glx_major, glx_minor;

	Window win;

	// FBConfigs were added in GLX version 1.3.
	if ( !glXQueryVersion( display, &glx_major, &glx_minor ) ||
			( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
	{
		printf("Invalid GLX version");
		exit(1);
	}

	printf( "Getting matching framebuffer configs\n" );

	int fbcount;

	GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &fbcount);
	if (!fbc)
	{
		printf( "Failed to retrieve a framebuffer config\n" );
		exit(1);
	}
	printf( "Found %d matching FB configs.\n", fbcount );

	// Pick the FB config/visual with the most samples per pixel
	printf( "Getting XVisualInfos\n" );
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

	int i;
	for (i=0; i<fbcount; ++i)
	{
		XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
		if ( vi )
		{
			int samp_buf, samples;
			glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
			glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );

			printf( "  Matching fbconfig %d, visual ID 0x%2x: SAMPLE_BUFFERS = %d,"
					" SAMPLES = %d\n",
					i, vi -> visualid, samp_buf, samples );

			if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
				best_fbc = i, best_num_samp = samples;
			if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
				worst_fbc = i, worst_num_samp = samples;
		}
		XFree( vi );
	}


	GLXFBConfig bestFbc = fbc[ best_fbc ];

	// Be sure to free the FBConfig list allocated by glXChooseFBConfig()
	XFree( fbc );

	// Get a visual
	vi = glXGetVisualFromFBConfig( display, bestFbc );
	printf( "Chosen visual ID = 0x%x\n", vi->visualid );

	printf( "Creating colormap\n" );
	XSetWindowAttributes swa;
	Colormap cmap;
	swa.colormap = cmap = XCreateColormap( display,
			RootWindow( display, vi->screen ),
			vi->visual, AllocNone );
	swa.background_pixmap = None ;
	swa.border_pixel      = 0;
	swa.event_mask        = StructureNotifyMask;

	printf( "Creating window\n" );
	win = XCreateWindow( display, RootWindow( display, vi->screen ),
			0, 0, width, height, 0, vi->depth, InputOutput,
			vi->visual,
			CWBorderPixel|CWColormap|CWEventMask, &swa );

	if ( !win )
	{
		printf( "Failed to create window.\n" );
		exit(1);
	}

	/* make an X GC so we can do XCopyArea later */
	gc = XCreateGC( display, win, 0, NULL );

	XStoreName( display, win, "GL 3.0 Window" );

	printf( "Mapping window\n" );
	XMapWindow( display, win );

	// Get the default screen's GLX extension list
	const char *glxExts = glXQueryExtensionsString( display,
			DefaultScreen( display ) );

	// NOTE: It is not necessary to create or make current to a context before
	// calling glXGetProcAddressARB
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
		glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

	// Install an X error handler so the application won't exit if GL 3.0
	// context allocation fails.
	//
	// Note this error handler is global.  All display connections in all threads
	// of a process use the same error handler, so be sure to guard against other
	// threads issuing X commands while this code is running.
	ctxErrorOccurred = false;
	int (*oldHandler)(Display*, XErrorEvent*) =
		XSetErrorHandler(&ctxErrorHandler);

	// Check for the GLX_ARB_create_context extension string and the function.
	// If either is not present, use GLX 1.3 context creation method.
	if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) ||
			!glXCreateContextAttribsARB )
	{
		printf( "glXCreateContextAttribsARB() not found"
				" ... using old-style GLX context\n" );
		ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
	}

	// If it does, try to get a GL 3.0 context!
	else
	{
		int context_attribs[] =
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
			GLX_CONTEXT_MINOR_VERSION_ARB, 0,
			//GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			None
		};

		printf( "Creating context\n" );
		ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
				True, context_attribs );

		// Sync to ensure any errors generated are processed.
		XSync( display, False );
		if ( !ctxErrorOccurred && ctx )
			printf( "Created GL 3.0 context\n" );
		else
		{
			// Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
			// When a context version below 3.0 is requested, implementations will
			// return the newest context version compatible with OpenGL versions less
			// than version 3.0.
			// GLX_CONTEXT_MAJOR_VERSION_ARB = 1
			context_attribs[1] = 1;
			// GLX_CONTEXT_MINOR_VERSION_ARB = 0
			context_attribs[3] = 0;

			ctxErrorOccurred = false;

			printf( "Failed to create GL 3.0 context"
					" ... using old-style GLX context\n" );
			ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
					True, context_attribs );
		}
	}

	// Sync to ensure any errors generated are processed.
	XSync( display, False );

	// Restore the original error handler
	XSetErrorHandler( oldHandler );

	if ( ctxErrorOccurred || !ctx )
	{
		printf( "Failed to create an OpenGL context\n" );
		exit(1);
	}

	// Verifying that context is a direct context
	if ( ! glXIsDirect ( display, ctx ) )
	{
		printf( "Indirect GLX rendering context obtained\n" );
	}
	else
	{
		printf( "Direct GLX rendering context obtained\n" );
	}

	return win;
}

static GLXPixmap create_pixmap (Display *display, Window win, unsigned int width,
		unsigned int height, Pixmap *pixmap)
{
	Pixmap pm;
	GLXPixmap glxpm;
	XWindowAttributes attr;

	pm = XCreatePixmap( display, win, width, height, vi->depth );
	if (!pm) {
		printf("Error: XCreatePixmap failed\n");
		exit(-1);
	}

	XGetWindowAttributes( display, win, &attr );

	/*
	 * IMPORTANT:
	 *   Use the glXCreateGLXPixmapMESA funtion when using Mesa because
	 *   Mesa needs to know the colormap associated with a pixmap in order
	 *   to render correctly.  This is because Mesa allows RGB rendering
	 *   into any kind of visual, not just TrueColor or DirectColor.
	 */
#if 0//def GLX_MESA_pixmap_colormap
	if (strstr(glXQueryExtensionsString(display, 0), "GLX_MESA_pixmap_colormap")) {
		/* stand-alone Mesa, specify the colormap */
		glxpm = glXCreateGLXPixmapMESA( display, vi, pm, attr.colormap );
	}
	else {
		glxpm = glXCreateGLXPixmap( display, vi, pm );
	}
#else
	/* This will work with Mesa too if the visual is TrueColor or DirectColor */
	glxpm = glXCreateGLXPixmap( display, vi, pm );
#endif

	if (!glxpm) {
		printf("Error: GLXCreateGLXPixmap failed\n");
		exit(-1);
	}

	*pixmap = pm;

	return glxpm;
}

int setup_gl_context()
{
	display = XOpenDisplay(0);
	if (!display)
	{
		printf("Failed to open X display\n");
		exit(1);
	}

	win = create_window(display, WINDOW_WIDTH, WINDOW_HEIGHT);
	glXMakeCurrent( display, win, ctx );
}

void terminate_gl_context()
{
}

void swap_buffers()
{
	glXSwapBuffers (display, win);
}
#endif
int main(int argc, char **argv)
{
	GLuint                       texYuv[4] = {0};

	if (setup_gl_context() < 0)
	{
		fprintf(stderr, "setup_gl_context failed.\n");
		exit(EXIT_FAILURE);
	}

	if(argc > 1)
		srv_select = atoi(argv[1]);

	if(argc > 2)
		srv_car = atoi(argv[2]);

	if(argc > 3)
		srv_bowl = atoi(argv[3]);

	if(argc > 4)
		srv_view = atoi(argv[4]);

	if(argc > 5)
		outfile = fopen(argv[5], "wb");

	render3DSRVObj.screen_width = WINDOW_WIDTH;
	render3DSRVObj.screen_height = WINDOW_HEIGHT;
	get_bmp_info("standalone/sa_front.bmp", &render3DSRVObj.cam_width,
			&render3DSRVObj.cam_height,
			&render3DSRVObj.cam_bpp);
	printf("Image width: %d, height: %d, bpp: %d\n",render3DSRVObj.cam_width,
			render3DSRVObj.cam_height,
			render3DSRVObj.cam_bpp);

#ifndef DYNAMIC_LUT
	render3DSRVObj.LUT3D = (void *) GAlignLUT;
#else
	// Set this to NULL. SRV code will generate the LUT if it is NULL.
	render3DSRVObj.LUT3D = NULL;
#endif
	render3DSRVObj.BoxLUT = (void *) BoxLUT;
	render3DSRVObj.BoxPose3D = (void *) BoxPose3D;

	if(render_setup(&render3DSRVObj) !=0 )
	{
		printf("render_setup failed\n");
		return 0;
	}


	printf("render_setup done\n");

	glGenTextures(1, &texYuv[0]);
	GL_CHECK(glGenTextures);
	glBindTexture(GL_TEXTURE_2D, texYuv[0]);
	GL_CHECK(glBindTexture);
	load_texture_bmp(texYuv[0], "standalone/sa_front.bmp");
	GL_CHECK(load_texture_bmp);

	glGenTextures(1, &texYuv[1]);
	GL_CHECK(glGenTextures);
	glBindTexture(GL_TEXTURE_2D, texYuv[1]);
	GL_CHECK(glBindTexture);
	load_texture_bmp(texYuv[1], "standalone/sa_right.bmp");
	GL_CHECK(load_texture_bmp);

	glGenTextures(1, &texYuv[2]);
	GL_CHECK(glGenTextures);
	glBindTexture(GL_TEXTURE_2D, texYuv[2]);
	GL_CHECK(glBindTexture);
	load_texture_bmp(texYuv[2], "standalone/sa_back.bmp");
	GL_CHECK(load_texture_bmp);

	glGenTextures(1, &texYuv[3]);
	GL_CHECK(glGenTextures);
	glBindTexture(GL_TEXTURE_2D, texYuv[3]);
	GL_CHECK(glBindTexture);
	load_texture_bmp(texYuv[3], "standalone/sa_left.bmp");
	GL_CHECK(load_texture_bmp);

	if(srv_render_to_file == true)
	{
		GLvoid *pixels = malloc(readwidth * readheight * 4);
		srv_param_select = 0;

		for (srv_param_view1 = 0; srv_param_view1 < 3; srv_param_view1++)
		{
			srv_param_view2 = (srv_param_view1+1)%3;

			for(int i = 0; i < num_iterations; i++)
			{
				intercepts xint, yint;
				int xcar, ycar;
				char cfilename[sizeof "geoAlignView2WorldMesh_vp_00_to_01_step_000.c"];
				sprintf(cfilename, "geoAlignView2WorldMesh_vp_%02d_to_%02d_step_%03d.c",
						srv_param_view1,
						srv_param_view2,
						srv_param_step);

				coutfile = fopen(cfilename, "wt");

				fprintf(coutfile, "const float vp%02d_to_%02d_step_%03dView2WorldMesh[] = {",
						srv_param_view1,
						srv_param_view2,
						srv_param_step);

				int wcwidth = (int)ceil(readwidth/subsample);
				int wcheight = (int)ceil(readheight/subsample);
				worldcoords ** wc = new worldcoords *[wcwidth];
				for(int cols = 0; cols < wcwidth; cols++)
					wc[cols] = new worldcoords[wcheight];

				srv_param_step = i;
				for(srv_param_select = 0; srv_param_select <= 3; srv_param_select++)
				{
					if(srv_param_select == 3)
					{
						srv_param_car = true;
						srv_param_bowl = false;
					}
					else
					{
						srv_param_car = false;
						srv_param_bowl = true;
					}

					render_renderFrame(
							&render3DSRVObj,
							NULL,
							texYuv
							);

					glFlush();
					glReadPixels(readx, ready, readwidth, readheight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

					int index_i, index_j;

					for(int j = 0, index_j = 0; j < readheight; j = j + subsample, index_j++)
					{
						int bytewidth = readwidth * 4;

						for(int i = 0, index_i = 0; i < bytewidth; i = i + 4 * subsample, index_i++)
						{
							uint8_t *p8 = (uint8_t *)pixels;
							uint8_t r = (uint8_t)p8[j*readwidth*4 + i];
							uint8_t g = (uint8_t)p8[j*readwidth*4 + i + 1];
							uint8_t b = (uint8_t)p8[j*readwidth*4 + i + 2];
							uint8_t a = (uint8_t)p8[j*readwidth*4 + i + 3];
							glm::vec4 rgba = glm::vec4((float)r, (float)g, (float)b, (float)a);
							glm::vec4 shft = glm::vec4(1.0, 1.0/256.0, 1.0/(256.0*256.0), 1.0/(256.0*256.0*256.0));
							float val;
							val = glm::dot(rgba, shft);
							switch(srv_param_select)
							{
								case 0:
									wc[index_i][index_j].x = val;
									break;
								case 1:
									wc[index_i][index_j].y = val;
									break;
								case 2:
									wc[index_i][index_j].z = val;
									break;
								default:
									break;
							}
						}
					}
					render_worldToScreen(&xcar, &ycar, 0, 0, 0);
					printf("Car cenrer: %d, %d\n", xcar, ycar);

					render_getIntercepts(&xint, &yint, 585, (585+752), 49, (49+1008));
					printf("X axis: xl: %d yl :%d xr: %d yr: %d xt: %d yt :%d xb: %d yb: %d \n",
							xint.l.x, xint.l.y, xint.r.x, xint.r.y,
							xint.t.x, xint.t.y, xint.b.x, xint.b.y);
					printf("Y axis: xl: %d yl :%d xr: %d yr: %d xt: %d yt :%d xb: %d yb: %d \n",
							yint.l.x, yint.l.y, yint.r.x, yint.r.y,
							yint.t.x, yint.t.y, yint.b.x, yint.b.y);

					char filename[sizeof "from_00_to_01_step_000_select_0.data"];
					sprintf(filename, "from_%02d_to_%02d_step_%03d_select_%01d.data",
							srv_param_view1,
							srv_param_view2,
							srv_param_step,
							srv_param_select);

					outfile = fopen(filename, "wb");
					fwrite(pixels, readwidth * readheight *4, 1, outfile);
					fclose(outfile);
					swap_buffers();
				}

				for(int j = 0; j < wcheight; j++)
				{
					for(int i = 0; i < wcwidth; i++)
					{
						if((j == (wcheight - 1)) && (i == (wcwidth - 1)))
							fprintf(coutfile, " %f, %f, %f", wc[i][j].x, wc[i][j].y, wc[i][j].z);
						else
							fprintf(coutfile, " %f, %f, %f,", wc[i][j].x, wc[i][j].y, wc[i][j].z);
					}
				}

				fprintf(coutfile, "};\n");
				fclose(coutfile);
			}
		}
	}
	else
	{
		srv_param_select = 3;
		srv_param_car = true;
		srv_param_bowl = true;
		while(srv_exit == false)
		{
			render_renderFrame(
					&render3DSRVObj,
					NULL,
					texYuv
					);
			swap_buffers();
		}

	}

	terminate_gl_context();

	exit(EXIT_SUCCESS);
}
