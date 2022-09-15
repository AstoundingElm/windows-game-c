#pragma once
#include "defines.h"
#define SDL_MAIN_HANDLED
#include <C:\Users\peter\OneDrive\Desktop\game\SDL2-2.24.0\include\SDL.h>

struct window_types{

  double window_width;
  double window_height;
  SDL_Window * window;

  
};

static window_types window_types_context;

PINLINE void init_window(window_types * window_context){

    window_context->window_width = 800;
    window_context->window_height = 600;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  if(SDL_Init(SDL_INIT_VIDEO) < 0){

    ERROR_EXIT("could not init sdl%s", SDL_GetError());
  }

  window_context->window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
  if(!window_context->window){

    ERROR_EXIT("failed to initi window%s", SDL_GetError());
    
  }

  SDL_GL_CreateContext(window_context->window);
  if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){

    ERROR_EXIT("couldnt init glad%s", SDL_GetError());    
    
  }

};
