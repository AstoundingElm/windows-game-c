#pragma once

#include "defines.h"

struct time_stats{

  f32 delta;
  f32 now;
  f32 last;

  f32 frame_last;
  f32 frame_delay;
  f32 frame_time;

  u32 frame_rate;
  u32 frame_count;
  

};

time_stats time_stats_context;

void time_init(u32 frame_rate, time_stats * time_context){

  time_context->frame_rate = frame_rate;
  time_context->frame_delay = 1000.f / frame_rate;

}

void time_update(time_stats * time_context){

  time_context->now = (f32)SDL_GetTicks();
  time_context->delta = (time_context->now - time_context->last) /1000.f;
  time_context->last = time_context->now;
  ++time_context->frame_count;

  if(time_context->now - time_context->frame_last >= 1000.f){

    time_context->frame_rate = time_context->frame_count;
    time_context->frame_count = 0;
    time_context->frame_last = time_context->now;

  }
}


PINLINE void time_update_late(time_stats * time_context){

  time_context->frame_time = (f32)SDL_GetTicks() - time_context->now;

  if(time_context->frame_delay > time_context->frame_time){

    SDL_Delay(time_context->frame_delay - time_context->frame_time);

  }
  

}
