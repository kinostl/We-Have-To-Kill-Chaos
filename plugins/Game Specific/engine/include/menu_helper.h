#ifndef FF_MENU_HELPER
#define FF_MENU_HELPER

#include <asm/types.h>

extern UBYTE _itoa_fmt_len;
UBYTE itoa_fmt(INT16 v, UBYTE *d) OLDCALL BANKED PRESERVES_REGS(b, c);

inline UBYTE itoa_format(INT16 v, UBYTE *d, UBYTE dlen) {
  _itoa_fmt_len = dlen;
  UBYTE len = itoa_fmt(v, d);
  return len;
}

#endif