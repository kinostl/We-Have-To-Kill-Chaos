const id = "FO_EVENT_EXPORT_PALETTES";
const groups = ["Plugins"];
const name = "Export Palettes";

const fields = (
  [{ label: "Export flags to C" }, { type: "text", key: "filter", placeholder: "Filter" }]
);

const hexDec = (hex) => parseInt(hex, 16);
const compileColor = (hex) => {
  const r = Math.floor(hexDec(hex.substring(0, 2)) * (32 / 256));
  const g = Math.floor(hexDec(hex.substring(2, 4)) * (32 / 256));
  const b = Math.max(1, Math.floor(hexDec(hex.substring(4, 6)) * (32 / 256)));
  return `RGB(${r}, ${g}, ${b})`;
};

const compile = (input, helpers) => {
  const whiteSpace = /\s/g;
  const {writeAsset} = helpers;

  if (!input.filter) throw "Filter is necessary, add a keyword to the ones you want";
  const filter = input.filter.toUpperCase();
  const palettes = helpers.palettes.filter((x) => x.name.toUpperCase().includes(filter));
  const palette_rgb = palettes.map((palette) => {
    const colors = palette.colors.map(compileColor);
    return `CGB_PALETTE(${colors[0]},${colors[1]},${colors[2]},${colors[3]})`
  });
  const palette_names = palettes.map((palette)=>{
    let name = palette.name;
    name = name.replaceAll(whiteSpace, '_');
    name = name.toUpperCase();
    return name
  })

  const palette_db = palette_names.map((x, i)=>{
    return `[${x}]=${palette_rgb[i]}`
  })

  writeAsset(
    `${filter.toLowerCase()}_palettes.h`,
      /*h*/`
#ifndef ${filter}_PALETTES_DEF
#define ${filter}_PALETTES_DEF

#include <gbs_types.h> // IWYU pragma: export
#include <asm/types.h> // IWYU pragma: export

typedef enum {
  NO_${filter}_PALETTE,
  ${palette_names.join(',\r  ')}
} ${filter}_PALETTES;

extern const palette_entry_t ${filter.toLowerCase()}_palette_db[];
void load_${filter.toLowerCase()}_palette(palette_entry_t * entry, ${filter}_PALETTES palette) BANKED;

BANKREF_EXTERN(${filter}_PALETTES_DEF)

#endif
`.trim()
  )

  writeAsset(
    `${filter.toLowerCase()}_palettes.c`,
      /*c*/`
#pragma bank 255
#include "data/${filter.toLowerCase()}_palettes.h"

const palette_entry_t ${filter.toLowerCase()}_palette_db[]={
  ${palette_db.join(',\r  ')}
};

void load_${filter.toLowerCase()}_palette(palette_entry_t * entry, ${filter}_PALETTES palette) BANKED {
  MemcpyBanked(entry, &${filter.toLowerCase()}_palette_db[palette], sizeof(palette_entry_t), BANK(${filter}_PALETTES_DEF));
}

BANKREF(${filter}_PALETTES_DEF)
`.trim()
  )
}

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };