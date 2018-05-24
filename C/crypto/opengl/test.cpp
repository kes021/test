#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>
#ifdef __APPLE__
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
#else
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

#include <math.h>
#include <time.h>
#include <unistd.h>


//-----------------------------------
// some globals
#define DESIRED_FPS 60.0

SDL_Surface* gDrawSurface = NULL;
int width = 800;
int height = 600;

//-----------------------------------
// Function prototypes
void InfLoop();
void SetupSDL();

//-----------------------------------
int main(int argc, char** argv)
{
    SetupSDL();
    InfLoop();
    return 0;
}


//-----------------------------------
// Setup SDL and OpenGL
void SetupSDL(void)
{
    // init video system
    const SDL_VideoInfo* vidinfo;
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr,"Failed to initialize SDL Video!\n");
        exit(1);
    }

    // tell system which funciton to process when exit() call is made
    atexit(SDL_Quit);

    // get optimal video settings
    vidinfo = SDL_GetVideoInfo();
    if(!vidinfo)
    {
        fprintf(stderr,"Coudn't get video information!\n%s\n", SDL_GetError());
        exit(1);
    }

    // set opengl attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       5);
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      32);
#else
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
#endif
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,    1);

    // get a framebuffer
    gDrawSurface = SDL_SetVideoMode(width,height,vidinfo->vfmt->BitsPerPixel,
        SDL_OPENGL);

    if( !gDrawSurface )
    {
        fprintf(stderr,"Couldn't set video mode!\n%s\n", SDL_GetError());
        exit(1);
    }

    // set opengl viewport and perspective view
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 120, 4.0f / 3.0f, .00001, 100);
    glMatrixMode(GL_MODELVIEW);

}

//-----------------------------------
// Infinite Loop
void InfLoop()
{
    //--- infinite loop with event queue processing
    SDL_Event event;
    while(1)
    {
        while( SDL_PollEvent( &event ))
        {
            switch( event.type )
            {
            case SDL_QUIT:
                exit(0);
                break;
            }

        } // -- while event in queue

    } // -- infinite loop
}
