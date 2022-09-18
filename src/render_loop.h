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

  render_init();
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

  SDL_ShowCursor(false);
  AABB test_aabb = {
    .position = {800 * 0.5, 600 * 0.5},
    .half_size = {50, 50}};

  AABB cursor_aabb = {.half_size = {75, 75}};

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
	  physics_update(&physics_types_context, &time_stats_context);
vec4 white = {1, 1, 1, 1};
 vec4 red = {1, 0, 0, 1};
 vec4 sub = {1,1,1,0.5};

 vec4 orange = {1, 0.5, 0, 1};
 
render_begin();
 cursor_aabb.position[0] = pos[0];
 cursor_aabb.position[1] = pos[1];

 
 render_aabb((f32*)&test_aabb, white);
 //render_aabb((f32*)&sum_aabb, sub);
 //render_aabb((f32*)&cursor_aabb, white);

 /* AABB minkowski_difference = aabb_minkowski_difference(test_aabb, cursor_aabb);
 render_aabb((f32*)&minkowski_difference, orange);

 vec2 intersect_test = {5, 5};
vec4 hard_code = { 1, 1, 1, 0.5};
 render_aabb((f32*) &test_aabb, hard_code);

 vec2 pv;
 vec4 cyan = {0, 1,1,1};
 aabb_penetration_vector(pv, minkowski_difference);

 AABB collision_aabb = cursor_aabb;
 collision_aabb = cursor_aabb;
 collision_aabb.position[0] += pv[0];
 collision_aabb.position[1] += pv[1];
 
 if(physics_aabb_intersect_aabb(test_aabb, cursor_aabb)){
   render_aabb((f32*)&cursor_aabb, red);
   render_aabb((f32*)&collision_aabb, cyan);
   vec2_add(pv, pos, pv);
   render_line_segment(pos, pv, cyan, &render_types_context, &shader_files_context);
 }else{
 render_aabb((f32*)&cursor_aabb, white);
 
 }
 vec4 tunnel = {1,1,1, 0.5};
 
 render_aabb((f32*)&start_aabb,tunnel);
 render_line_segment(start_aabb.position, pos, white, &render_types_context, &shader_files_context);
 if(physics_point_intersect(pos, test_aabb))
   
   render_quad(pos, intersect_test, red, &shader_files_context, &render_types_context);
 else
   render_quad(pos, intersect_test, white, &shader_files_context, &render_types_context);
 */
//render_quad(pos, test2,test3, &shader_files_context, &render_types_context);
/*vec4 int_vec = {1, 0, 0, 1};
 for(u32 i = 0; i < body_count; ++i){

   Body * body = physics_body_get(i, &physics_types_context);
   render_quad(body->aabb.position, body->aabb.half_size, int_vec, &shader_files_context, &render_types_context);
   if(body->aabb.position[0] > 800 || body->aabb.position[0] < 0)
     body->velocity[0] *= -1;
   if(body->aabb.position[1] > 600 || body->aabb.position[1] < 0)
     body->velocity[1] *= -1;

   if(body->velocity[0] > 500)
     body->velocity[0] = 500;
   if(body->velocity[0] < -500)
     body->velocity[0] = -500;
   if(body->velocity[1] > 500)
     body->velocity[1] = 500;
   if(body->velocity[1] < -500)
     body->velocity[1] = -500;
   
 }
*/
 
 
    render_end( &window_types_context);
    time_update_late(&time_stats_context);
  }



};

