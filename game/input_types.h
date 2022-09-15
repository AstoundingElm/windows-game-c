#pragma once



enum input_key{

  INPUT_KEY_LEFT,
  INPUT_KEY_RIGHT,
  INPUT_KEY_UP,
  INPUT_KEY_DOWN,
  INPUT_KEY_ESCAPE

};

enum key_state{

  KS_UNPRESSED,
  KS_PRESSED,
  KS_HELD,
  
};

struct input_state{


  key_state left;
  key_state right;
  key_state down;
  key_state up;
  key_state escape;

};
