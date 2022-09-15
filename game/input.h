#pragma once

#include "defines.h"
#include "input_types.h"
PINLINE void input_update(){
  const u8 * keyboard_state = SDL_GetKeyboardState(NULL);
 /* update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &inputcontext.left);
  update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &inputcontext.left);
  update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &inputcontext.left);
  update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &inputcontext.left);
  */
};

PINLINE void update_key_state(u8 current_state, key_state * internal_key_state){

  if(current_state){

    if(*internal_key_state > 0)
      *internal_key_state = KS_HELD;
    else
      *internal_key_state = KS_PRESSED;
  }else{*internal_key_state = KS_UNPRESSED;
  }
  
}

