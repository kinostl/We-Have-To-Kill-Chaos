#include <asm/types.h>
#include <gb/gb.h>
#include <vm.h>
#pragma bank 255

#include "actor.h"
#include "input.h"
#include "load_font_into_bg.h"
#include "math.h"

#include "states/string_input.h"

point16_t string_input_base_pos;
point16_t string_input_max_pos;
point16_t string_input_curr_pos;

UBYTE string_input_timer;
const char string_input_alphabet[6][8]={
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
    {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
    {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
    {'Y', 'Z', ' ', '0', '1', '2', '3', '4'},
    {'?', '\'', ',', '5', '6', '7', '8', '9'},
    {'.', '-', '.', '!', '.', '.', '.', '\0'},
};

void string_input_init(void) BANKED {
  string_input_timer = 7;
  string_input_base_pos = PLAYER.pos;

  string_input_curr_pos.x = 0;
  string_input_curr_pos.y = 0;

  string_input_max_pos.x = 7;
  string_input_max_pos.y = 5;

  PLAYER.pos.x = ((PLAYER.pos.x >> 7) << 7);
  PLAYER.pos.y = ((PLAYER.pos.y >> 7) << 7);
}

void string_input_update(void) BANKED {
  // Updates are counted in Frames, 6 Frames is 0.1 Seconds
  if (string_input_timer < 6) {
    string_input_timer++;
    return;
  }

  string_input_timer = 0;

  if (INPUT_RECENT_LEFT) {
    string_input_curr_pos.x--;
    if (string_input_curr_pos.x < 0) {
      string_input_curr_pos.x = string_input_max_pos.x;
    }
  } else if (INPUT_RECENT_RIGHT) {
    string_input_curr_pos.x++;
    if (string_input_curr_pos.x > string_input_max_pos.x) {
      string_input_curr_pos.x = 0;
    }
  } else if (INPUT_RECENT_UP) {
    string_input_curr_pos.y--;
    if (string_input_curr_pos.y < 0) {
      string_input_curr_pos.y = string_input_max_pos.y;
    }
  } else if (INPUT_RECENT_DOWN) {
    string_input_curr_pos.y++;
    if (string_input_curr_pos.y > string_input_max_pos.y) {
      string_input_curr_pos.y = 0;
    }
  }

  PLAYER.pos.y = ((string_input_base_pos.y + (string_input_curr_pos.y * 256)) >> 7) << 7;
  PLAYER.pos.x = ((string_input_base_pos.x + (string_input_curr_pos.x * 256)) >> 7) << 7;
}