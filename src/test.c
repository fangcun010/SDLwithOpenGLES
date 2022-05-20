#include <stdio.h>
#include <stdlib.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char* msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}


void checkSDLError(int line)
{
#ifndef NDEBUG
    const char* error = SDL_GetError();
    if (*error != '\0')
    {
        printf("SDL Error: %s\n", error);
        if (line != -1)
            printf(" + line: %i\n", line);
        SDL_ClearError();
    }
#endif
}

/* Our program's entry point */
int main(int argc, char* argv[])
{
    SDL_Window* mainwindow; /* Our window handle */
    SDL_GLContext maincontext = NULL; /* Our opengl context handle */

    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    mainwindow = SDL_CreateWindow("SDL with OpenGLES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        512, 512, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");

    checkSDLError(__LINE__);

    SDL_GLContext context = SDL_GL_CreateContext(mainwindow);
    SDL_GL_MakeCurrent(mainwindow, context);

    printf("\n%s", glGetString(GL_RENDERER));
    printf("\n%s", glGetString(GL_VENDOR));
    printf("\n%s", glGetString(GL_VERSION));
    printf("\n%s",glGetString(GL_SHADING_LANGUAGE_VERSION));

    while (1) {
        SDL_Event e;

        SDL_PollEvent(&e);

        glClearColor(0.5, 0.5, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(mainwindow);
    }

    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    return 0;
}