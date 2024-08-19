#ifndef FF_MENU_HELPER
#define FF_MENU_HELPER

#include "armor_data.h"
#include "string.h"
#include "weapon_data.h"
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

void add_armor_sym(unsigned char *d, enum A_TYPE sym_id) OLDCALL BANKED;
void add_weapon_sym(unsigned char *d, enum W_TYPE sym_id) OLDCALL BANKED;
inline void add_potion_sym(unsigned char *d) {
  const unsigned char sym[2] = {143, '\0'};
  strcat(d, sym);
}

inline void add_new_line(unsigned char *d, UBYTE i) {
  progress_blanks(d, i - (strlen(d) % i));
}

void armor_name_short_cat(BYTE item_id, enum A_TYPE type,unsigned char *item_s) OLDCALL BANKED;
void weapon_name_short_cat(BYTE item_id, unsigned char *item_s) OLDCALL BANKED;
#endif