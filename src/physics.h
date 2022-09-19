#pragma once

#include "linmath/linmath.h"
#include "list.h"
#include "defines.h"
#include "time.h"
static u32 iterations = 2;
static f32 tick_rate;

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
  f32 gravity;
  f32 terminal_velocity;
  Array_List * static_body_list;
};

struct Static_Body{

  AABB aabb;

};

struct Hit{

  bool is_hit;
  f32 time;
  vec2 position;
  vec2 normal;
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
    

/*PINLINE void physics_update(physics_types * physics_context, time_stats * time_context){

  Body * body;
  

  for(u32 i = 0; i < physics_context->body_list->len; i++){

    body = (Body *)array_list_get(physics_context->body_list, i);
    body->velocity[0] += body->acceleration[0] * time_context->delta;
    body->velocity[1] += body->acceleration[1] * time_context->delta;
    body->aabb.position[0] += body->velocity[0] * time_context->delta;
    body->aabb.position[1] += body->velocity[1] * time_context->delta;
    
  }

};
*/

Body * physics_static_body_get(size_t index, physics_types * physics_context){

  return (Body *)array_list_get(physics_context->static_body_list, index);

}

Hit ray_intersect_aabb(vec2 pos, vec2 magnitude, AABB aabb) {
	Hit hit = {0};
	vec2 min, max;
	aabb_min_max(min, max, aabb);

	f32 last_entry = -INFINITY;
	f32 first_exit = INFINITY;

	for (u8 i = 0; i < 2; ++i) {
		if (magnitude[i] != 0) {
			f32 t1 = (min[i] - pos[i]) / magnitude[i];
			f32 t2 = (max[i] - pos[i]) / magnitude[i];

			last_entry = fmaxf(last_entry, fminf(t1, t2));
			first_exit = fminf(first_exit, fmaxf(t1, t2));
		} else if (pos[i] <= min[i] || pos[i] >= max[i]) {
			return hit;
		}
	}

	if (first_exit > last_entry && first_exit > 0 && last_entry < 1) {
		hit.position[0] = pos[0] + magnitude[0] * last_entry;
		hit.position[1] = pos[1] + magnitude[1] * last_entry;

		hit.is_hit = true;
		hit.time = last_entry;
		f32 dx = hit.position[0] - aabb.position[0];
		f32 dy = hit.position[1] - aabb.position[1];

		f32 px = aabb.half_size[0] - fabsf(dx);
		f32 py = aabb.half_size[1] - fabsf(dy);

		if(px < py){
		  hit.normal[0] = (dx > 0) - (dx < 0);
		  
		} else{

		  hit.normal[1] = (dy > 0)  - (dy < 0);
		}
	}

	return hit;
}




PINLINE Hit sweep_static_bodies(AABB aabb, vec2 velocity, physics_types * physics_context){

   Hit result = {.time = 0xBEEF};

 for (u32 i = 0; i < physics_context->static_body_list->len; ++i) {
   Static_Body *static_body = (Static_Body *)physics_static_body_get(i,&physics_types_context);

		AABB sum_aabb = static_body->aabb;
		vec2_add(sum_aabb.half_size, sum_aabb.half_size, aabb.half_size);

		Hit hit = ray_intersect_aabb(aabb.position, velocity, sum_aabb);
		if (!hit.is_hit) {
			continue;
		}

		if (hit.time < result.time) {
			result = hit;
		} else if (hit.time == result.time) {
			// Solve highest velocity axis first.
			if (fabsf(velocity[0]) > fabsf(velocity[1]) && hit.normal[0] != 0) {
				result = hit;
			} else if (fabsf(velocity[1]) > fabsf(velocity[0]) && hit.normal[1] != 0) {
				result = hit;
			}
		}
	}

	return result;


   } 
 


 PINLINE void stationary_response(Body * body, physics_types * physics_context){


   for(u32 i = 0; i < physics_context->static_body_list->len; ++i){

     Static_Body * static_body = (Static_Body *)physics_static_body_get(i, &physics_types_context);
     AABB aabb = aabb_minkowski_difference(static_body->aabb, body->aabb);
     vec2 min, max;
     aabb_min_max(min, max, aabb);

     if(min[0] <= 0 && max[0] >= 0 && min[1] <= 0 && max[1] >= 0){

       vec2 penetration_vector;
       aabb_penetration_vector(penetration_vector, aabb);
       vec2_add(body->aabb.position, body->aabb.position, penetration_vector);

       
     }
     
   }
   
 }


 PINLINE void sweep_response(Body * body, vec2 velocity){

   Hit hit = sweep_static_bodies(body->aabb, velocity, &physics_types_context);

   if(hit.is_hit){

     body->aabb.position[0] = hit.position[0];
     body->aabb.position[1] = hit.position[1];

     if(hit.normal[0] != 0){

       body->aabb.position[1] += velocity[1];
       body->velocity[0] = 0;
     }else if(hit.normal[1] != 0){
       body->aabb.position[0] += velocity[0];
       body->velocity[1] = 0;
       
     }else{

       vec2_add(body->aabb.position, body->aabb.position, velocity);
     }
   }
   
   
   
 };


void physics_update(time_stats * time_context, physics_types * physics_context){

	  Body * body;
  

  for(u32 i = 0; i < physics_context->body_list->len; i++){

    body = (Body *)array_list_get(physics_context->body_list, i);
    body->velocity[1] += physics_context->gravity;
    if(physics_context->terminal_velocity > body->velocity[1]){

	body->velocity[1] = physics_context->terminal_velocity;
      };
      body->velocity[0] += body->acceleration[0];// * time_context->delta;
      body->velocity[1] += body->acceleration[1]; // * time_context->delta;

      vec2 scaled_velocity;
      vec2_scale(scaled_velocity, body->velocity, time_context->delta * tick_rate);

      for(u32 j = 0; j < iterations; ++j){

	sweep_response(body, scaled_velocity);
	stationary_response(body,&physics_types_context);
      }
      
    //body->aabb.position[0] += body->velocity[0] * time_context->delta;
    //body->aabb.position[1] += body->velocity[1] * time_context->delta;
    
  }

}

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

size_t physics_static_body_create(vec2 position, vec2 size, physics_types * physics_context){

  Static_Body static_body = {
    .aabb = {
      .position = {position[0], position[1]},
      .half_size = {size[0] * (float)0.5, size[1] *(float)0.5},
    }
  };
    if(array_list_append(physics_context->static_body_list, &static_body) == (size_t) -1)
      ERROR_EXIT("couldnt appende body to list");

    return physics_context->static_body_list->len -1;
}


