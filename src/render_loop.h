#pragma once

#include "defines.h"
#include "config.h"
#include "render.h"
#include "window_types.h"
#include "time.h"
#include "linmath/linmath.h"
#include "physics.h"
vec2 test{ 800 * 0.5, 600 * 0.5 };
vec2 test2{ 50, 50 };
vec4 test3{ 0, 1,0,  1 };

static vec2 pos;

static void input_handle(input_state * input_context, time_stats * time_context){

  /* if(input_context->left == KS_PRESSED || input_context->left == KS_HELD)
    pos[0] -= 500 * time_context->delta;
  if(input_context->right == KS_PRESSED || input_context->right == KS_HELD)
    pos[0] += 500 * time_context->delta;
  if(input_context->up == KS_PRESSED || input_context->up == KS_HELD)
    pos[1] += 500 * time_context->delta;
  if(input_context->down == KS_PRESSED || input_context->down == KS_HELD)
  pos[1] -= 500 * time_context->delta;*/
    if(input_context->escape == KS_PRESSED || input_context->escape == KS_HELD)
    running = false;

    i32 x, y;
    SDL_GetMouseState(&x, &y);
    pos[0] = (f32)x;
    pos[1] = 600 -y;
    


}



PINLINE void main_loop(){
  time_init(60, &time_stats_context);
  config_init();
  init_window(&window_types_context);

  render_init(&physics_types_context);
  physics_init(&physics_types_context);

  /*u32 body_count = 100;



  for(u32 i = 0; i < body_count; ++i){
vec2 test_vec = {rand() % 800, rand() % 600};
vec2 test_vec2 = {rand()%100, rand() % 100};
    size_t body_index = physics_body_create(
	     test_vec,
	     test_vec2, &physics_types_context);
    Body * body = physics_body_get(body_index, &physics_types_context);
    body->acceleration[0] = rand() % 200 - 100;
    body->acceleration[1] = rand() % 200 - 100;
    

  }
  */
  pos[0] = 800 * 0.5;
  pos[1] = 600 * 0.5;
vec2 fivefive = {5, 5};
	
  SDL_ShowCursor(false);
  AABB test_aabb = {
    .position = {800 * 0.5, 600 * 0.5},
    .half_size = {50, 50}};

  AABB cursor_aabb = {.half_size = {75, 75}};
  vec4 faded = {1, 1, 1, 0.3};
  AABB sum_aabb = {
    .position = {test_aabb.position[0], test_aabb.position[1]},
    .half_size = {test_aabb.half_size[0] + cursor_aabb.half_size[0],
		  test_aabb.half_size[1] + cursor_aabb.half_size[1]}};

  AABB start_aabb = {.half_size = {75, 75}};
  while (running) {
    time_update(&time_stats_context);
	  SDL_Event event;
	  while (SDL_PollEvent(&event)) {

		  switch (event.type) {
		  case SDL_QUIT:
			  running = false;
			  break;
		  case SDL_MOUSEBUTTONDOWN:
		    if(event.button.button = SDL_BUTTON_LEFT){
		      start_aabb.position[0] = pos[0];
		      start_aabb.position[1]  = pos[1];
		    }
		  default: break;

		  }
	  }


	  input_update(&config_types_context);
	  input_handle(&input_state_context, &time_stats_context);
	  physics_update( &time_stats_context, &physics_types_context);
vec4 white = {1, 1, 1, 1};
 vec4 red = {1, 0, 0, 1};
 vec4 sub = {1,1,1,0.5};
vec4 cyan = {0,1,1,1};
 vec4 orange = {1, 0.5, 0, 1};
 
render_begin();
cursor_aabb.position[0] = pos[0];
		cursor_aabb.position[1] = pos[1];

		render_aabb((f32*)&test_aabb, white);

		vec4 faded = {1, 1, 1, 0.3};

		if (physics_aabb_intersect_aabb(test_aabb, cursor_aabb)) {
			render_aabb((f32*)&cursor_aabb, red);
		} else {
			render_aabb((f32*)&cursor_aabb, white);
		}

		render_aabb((f32*)&start_aabb, faded);
		render_line_segment(start_aabb.position, pos, faded, &render_types_context, &shader_files_context);
		
		f32 x = sum_aabb.position[0];
		f32 y = sum_aabb.position[1];
		f32 size = sum_aabb.half_size[0];
		vec2 greg_ = {0, y - size}; 
						vec2 t = {x - size, 0};
						vec2 u = {x - size, 600};
						vec2 v = {x + size, 0};
						vec2 testy = {x + size, 600};
						vec2 wow = {800, y - size};
						vec2 p = {0, y + size};
						vec2 k = {800, y + size};
		render_line_segment(t, u, faded, &render_types_context, &shader_files_context);
		render_line_segment(v, testy, faded,&render_types_context, &shader_files_context);
		render_line_segment(greg_, wow, faded,&render_types_context, &shader_files_context);
		render_line_segment(p, k, faded,&render_types_context, &shader_files_context);

		vec2 min, max;
		aabb_min_max(min, max, sum_aabb);

		vec2 magnitude;
		vec2_sub(magnitude, pos, start_aabb.position);

		Hit hit = ray_intersect_aabb(start_aabb.position, magnitude, sum_aabb);

		if (hit.is_hit) {
			AABB hit_aabb = {
				.position = {hit.position[0], hit.position[1]},
				.half_size = {start_aabb.half_size[0], start_aabb.half_size[1]}
			};
			render_aabb((f32*)&hit_aabb, cyan);
			render_quad(hit.position, fivefive, cyan, &shader_files_context, &render_types_context);
		}
	for (u8 i = 0; i < 2; ++i) {
			if (magnitude[i] != 0) {
				f32 t1 = (min[i] - pos[i]) / magnitude[i];
				f32 t2 = (max[i] - pos[i]) / magnitude[i];

				vec2 point;
				vec2_scale(point, magnitude, t1);
				vec2_add(point, point, pos);
				if (min[i] < start_aabb.position[i])
					render_quad(point, fivefive, orange, &shader_files_context, &render_types_context);
				else
					render_quad(point, fivefive, cyan, &shader_files_context, &render_types_context);

				vec2_scale(point, magnitude, t2);
				vec2_add(point, point, pos);
				if (max[i] < start_aabb.position[i])
					render_quad(point, fivefive, cyan, &shader_files_context, &render_types_context);
				else
					render_quad(point, fivefive, orange, &shader_files_context, &render_types_context);
			}
		}
	   
    render_end( &window_types_context);
    time_update_late(&time_stats_context);
  }



};

