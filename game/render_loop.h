#pragma once

#include "defines.h"

#include "render.h"
#include "window_types.h"
#include "linmath/linmath.h"

vec2 test{ 800 * 0.5, 600 * 0.5 };
vec2 test2{ 50, 50 };
vec4 test3{ 0, 1,0,  1 };

PINLINE void main_loop(){
 
  init_window(&window_types_context);

  render_init();
  
  bool running = true;

  while (running) {

	  SDL_Event event;
	  while (SDL_PollEvent(&event)) {

		  switch (event.type) {
		  case SDL_QUIT:
			  running = false;
			  break;
		  default: break;

		  }
	  }

	
render_begin();

render_quad(test, test2,test3, &shader_files_context, &render_types_context);


    render_end( &window_types_context);

  }



};

