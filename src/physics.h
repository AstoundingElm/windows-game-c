#pragma once

#include "linmath/linmath.h"
#include "list.h"
#include "defines.h"

struct AABB{

  vec2 position;
  vec2 half_size;

};

struct Body{

  AABB aabb;
  vec2 velocity;
  vec2 acceleration;
};

struct physics_types{

  Array_List * body_list;

};


static physics_types physics_types_context;

PINLINE AABB  aabb_minkowski_difference(AABB a, AABB b){

  AABB result;
  vec2_sub(result.position, a.position, b.position);
  vec2_add(result.half_size, a.half_size, b.half_size);

  return result;
};

PINLINE void physics_init(physics_types * physics_context ){

  physics_context->body_list = array_list_create(sizeof(Body), 0);

};

PINLINE void aabb_min_max(vec2 min, vec2 max, AABB aabb){

  vec2_sub(min, aabb.position, aabb.half_size);
  vec2_add(max, aabb.position, aabb.half_size);
}

PINLINE bool physics_point_intersect(vec2 point, AABB aabb){

  vec2 min, max;
  aabb_min_max(min, max, aabb);
  return point[0] >= min[0] &&
    point[0] <= max[0] &&
    point[1] >= min[1] &&
    point[1] <= max[1];
  
};

PINLINE bool physics_aabb_intersect_aabb(AABB a, AABB b){

  vec2 min, max;
  aabb_min_max(min, max, aabb_minkowski_difference(a, b));
  return (min[0] <= 0 && max[0] >= 0 && min[1] <= 0 && max[1] >=0);
  
};

PINLINE void aabb_penetration_vector(vec2 r, AABB aabb){

  vec2 min, max;
  aabb_min_max(min, max, aabb);
  f32 min_dist = fabsf(min[0]);
  r[0] = min[0];
  r[1] = 0;

  if(fabsf(max[0]) < min_dist){
    min_dist = fabsf(max[0]);
      r[0]  = max[0];
    }

  if(fabsf(min[1]) < min_dist){
	min_dist = fabsf(min[1]);
	r[0] = 0;
	r[1] = min[1];
	
      };

      if(fabsf(max[1]) < min_dist){

	r[0]  = 0;
	r[1] = max[1];
	
      }

  
      }
    

PINLINE void physics_update(physics_types * physics_context, time_stats * time_context){

  Body * body;
  

  for(u32 i = 0; i < physics_context->body_list->len; i++){

    body = (Body *)array_list_get(physics_context->body_list, i);
    body->velocity[0] += body->acceleration[0] * time_context->delta;
    body->velocity[1] += body->acceleration[1] * time_context->delta;
    body->aabb.position[0] += body->velocity[0] * time_context->delta;
    body->aabb.position[1] += body->velocity[1] * time_context->delta;
    
  }

};

PINLINE size_t physics_body_create(vec2 position, vec2 size, physics_types * physics_context){

  Body body = {.aabb = {.position = {position[0], position[1]},
			.half_size = {(float)size[0] * (float)0.5, (float)size[1] * (float)0.5},
    },
	       .velocity = {0,0},
  };

  if(array_list_append(physics_context->body_list, &body) == (size_t)-1)
    ERROR_EXIT("couldtn append body");
  return physics_context->body_list->len - 1;

}

Body * physics_body_get(size_t index, physics_types * physics_context){

  return (Body *)array_list_get(physics_context->body_list,  index);

}
