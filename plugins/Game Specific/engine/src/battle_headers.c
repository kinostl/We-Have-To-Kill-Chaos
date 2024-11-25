#include "handle_flashing.h"
#pragma bank 255
#include "enums.h"
#include "battle_headers.h"
#include "data/tileset_headers_fields.h"

const battle_header battle_header_db[] = {
    [FIELD]={
        .header = &tileset_headers_fields,
        .bank = BANK(tileset_headers_fields),
        .colors = {},
    },
};

UBYTE load_battle_header(UBYTE vram_ptr, BATTLE_ID battle_id) BANKED {
    battle_header header;

  MemcpyBanked(&header, &battle_header_db[battle_id], sizeof(battle_header), BANK(FF_BATTLE_HEADERS));

  const tileset_t * t_set = header.header;
  UWORD n_tiles = ReadBankedUWORD(&(t_set->n_tiles), header.bank);
  UBYTE * data = t_set->tiles;

  SetBankedBkgData(vram_ptr, n_tiles, data, header.bank);
  return n_tiles; // New end of available VRAM
}

void draw_battle_header(UBYTE vram_ptr) BANKED {
  UBYTE buf[10 * 4];
  for (UBYTE i = 0; i < 10 * 4; i++)
    buf[i] = vram_ptr + i;

  set_bkg_tiles(1, 1, 10, 4, buf);
  handle_bkg_set_color(0, 1, 1, 10, 4);
}

BANKREF(FF_BATTLE_HEADERS)