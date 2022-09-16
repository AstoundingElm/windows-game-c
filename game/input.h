#pragma once

#include "defines.h"
#include "input_types.h"

struct config{

  u8 keybinds[5];

};

static config config_types_context;

PINLINE void update_key_state(u8 current_state, key_state * internal_key_state){

  if(current_state){

    if(*internal_key_state > 0)
      *internal_key_state = KS_HELD;
   else
      *internal_key_state = KS_PRESSED;
  }else{
    *internal_key_state = KS_UNPRESSED;
  }
  
};



PINLINE void input_update(config * config_context){
  const u8 * keyboard_state = SDL_GetKeyboardState(NULL);
  update_key_state(keyboard_state[config_context->keybinds[INPUT_KEY_LEFT]], &input_state_context.left);
  update_key_state(keyboard_state[config_context->keybinds[INPUT_KEY_RIGHT]], &input_state_context.right);
  update_key_state(keyboard_state[config_context->keybinds[INPUT_KEY_UP]], &input_state_context.up);
  update_key_state(keyboard_state[config_context->keybinds[INPUT_KEY_DOWN]], &input_state_context.down);
  update_key_state(keyboard_state[config_context->keybinds[INPUT_KEY_ESCAPE]], &input_state_context.escape);
  
};


