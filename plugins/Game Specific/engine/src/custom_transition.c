#include <asm/types.h>
#include <gb/gb.h>
#include <gb/hardware.h>
#include <rand.h>
#pragma bank 255

struct screen_xy {
    BYTE x;
    BYTE y;
};

void pepperScreen(void) OLDCALL BANKED {
//   struct screen_xy pos[20 * 18];
//   int i = 0;
//   for (int y = 0; y < 18; y++) {
//     for (int x = 0; x < 20; x++) {
//       pos[i].x = x;
//       pos[i].y = y;
//       i++;
//     }
//   }

//   int rand_i;
//   struct screen_xy temp;
//   for (i = 0; i < (20 * 18); i++) {
//     rand_i = rand() % (20 * 18);
//     temp = pos[rand_i];
//     pos[rand_i] = pos[i];
//     pos[i] = temp;
//   }

// //   for (i = 0; i < (20 * 18); i++) {
// //     VBK_REG = 1;
// //     set_win_tile_xy(pos[i].x, pos[i].y, 0);
// //     VBK_REG = 0;
// //     set_win_tile_xy(pos[i].x, pos[i].y, 0);
// //     vsync();
// //   }
//   for (i = 0; i < (20 * 18); i++) {
//     VBK_REG = 1;
//     set_win_tile_xy(pos[i].x, pos[i].y, 7);
//     vsync();
//   }
//   VBK_REG = 0;
}