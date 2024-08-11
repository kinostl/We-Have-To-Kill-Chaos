#ifndef FF_MENU_HELPER
#define FF_MENU_HELPER

#include "string.h"
#include <asm/types.h>

extern UBYTE _itoa_fmt_len;
UBYTE itoa_fmt(INT16 v, UBYTE *d) OLDCALL BANKED PRESERVES_REGS(b, c);

inline UBYTE itoa_format(INT16 v, UBYTE *d, UBYTE dlen) {
  _itoa_fmt_len = dlen;
  UBYTE len = itoa_fmt(v, d);
  return len;
}

inline void fill_space(unsigned char *d, UBYTE len, unsigned char c) {
  unsigned char buf[2] = {c, '\0'};
  for (int i = 0; i < len; i++) {
    strcat(d, buf);
  }
}

inline void progress_blanks(unsigned char *d, UBYTE len) {
  fill_space(d, len, ' ');
}

void add_armor_sym(unsigned char *d, BYTE sym_id) OLDCALL BANKED;
void add_weapon_sym(unsigned char *d, BYTE sym_id) OLDCALL BANKED;
inline void add_potion_sym(unsigned char *d) {
  const unsigned char sym[2] = {143, '\0'};
  strcat(d, sym);
}

inline void add_new_line(unsigned char *d, UBYTE i) {
  progress_blanks(d, i - (strlen(d) % i));
}

#define make_box(x, y, w, h)                                                   \
  UBYTE menu[w * h] = "";                                                      \
  unsigned char border_char = 128;                                             \
  fill_space(menu, 1, border_char);                                            \
  border_char++;                                                               \
  fill_space(menu, 18, border_char);                                           \
  border_char++;                                                               \
  fill_space(menu, 1, border_char);                                            \
  border_char++;                                                               \
  for (BYTE i = 0; i < (h - 2); i++) {                                         \
    fill_space(menu, 1, border_char);                                          \
    border_char++;                                                             \
    fill_space(menu, 18, border_char);                                         \
    border_char++;                                                             \
    fill_space(menu, 1, border_char);                                          \
    border_char -= 2;                                                          \
  }                                                                            \
  border_char += 3;                                                            \
  fill_space(menu, 1, border_char);                                            \
  border_char++;                                                               \
  fill_space(menu, 18, border_char);                                           \
  border_char++;                                                               \
  fill_space(menu, 1, border_char);                                            \
  for (UBYTE i = 0; i < (w * h); i++) {                                        \
    UBYTE j = menu[i];                                                         \
    menu[i] = ReadBankedUBYTE(bg_font.recode_table + j, bg_font_bank);         \
    menu[i] += start_of_bkg_vram;                                              \
  }                                                                            \
  set_bkg_tiles(x, y, w, h, menu);

#endif