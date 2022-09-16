#pragma once

#include "defines.h"
#include "config.h"
#include "render.h"
#include "window_types.h"
#include "time.h"
#include "linmath/linmath.h"

vec2 test{ 800 * 0.5, 600 * 0.5 };
vec2 test2{ 50, 50 };
vec4 test3{ 0, 1,0,  1 };

static vec2 pos;

static void input_handle(input_state * input_context, time_stats * time_context){

  if(input_context->left == KS_PRESSED || input_context->left == KS_HELD)
    pos[0] -= 500 * time_context->delta;
  if(input_context->right == KS_PRESSED || input_context->right == KS_HELD)
    pos[0] += 500 * time_context->delta;
  if(input_context->up == KS_PRESSED || input_context->up == KS_HELD)
    pos[1] += 500 * time_context->delta;
  if(input_context->down == KS_PRESSED || input_context->down == KS_HELD)
    pos[1] -= 500 * time_context->delta;
    if(input_context->escape == KS_PRESSED || input_context->escape == KS_HELD)
    running = false;


}

PINLINE void main_loop(){
  time_init(60, &time_stats_context);
  config_init();
  init_window(&window_types_context);

  render_init();

  pos[0] = 800 * 0.5;
  pos[1] = 600 * 0.5;
  while (running) {
    time_update(&time_stats_context);
	  SDL_Event event;
	  while (SDL_PollEvent(&event)) {

		  switch (event.type) {
		  case SDL_QUIT:
			  running = false;
			  break;
		  default: break;

		  }
	  }


	  input_update(&config_types_context);
	  input_handle(&input_state_context, &time_stats_context);
	  
render_begin();

render_quad(pos, test2,test3, &shader_files_context, &render_types_context);


    render_end( &window_types_context);
    time_update_late(&time_stats_context);
  }



};

