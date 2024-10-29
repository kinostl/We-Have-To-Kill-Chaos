const id = "FO_EVENT_EXPORT_FLAGS";
const groups = ["Plugins"];
const name = "Export Flags";

const fields = (
  []
);


const compile = (input, helpers) => {
  const whiteSpace = /\s/g;
  const { variablesLookup, writeAsset } = helpers;
  const vFlags = Object.values(variablesLookup).filter((variable) => variable.flags);
  for (const vFlag of vFlags) {
    const vEnumName = vFlag.name.replaceAll(whiteSpace, '_').toUpperCase();
    const vEnum = new Array(16).fill(0).map((curr, idx) => {
      let vFlagName = vFlag.flags[`flag${idx+1}`];
      if (!vFlagName) {
        vFlagName = `FLAG_${idx}`;
      }
      vFlagName = vFlagName.replaceAll(whiteSpace, '_').toUpperCase();

      return `${vEnumName}_${vFlagName} = 1 << ${idx}`
    })

    writeAsset(
      `${vEnumName.toLowerCase()}_flags.h`,
      /*h*/`
#ifndef ${vEnumName}_FLAGS
#define ${vEnumName}_FLAGS
typedef enum {
  ${vEnum.join(',\r  ')}
} ${vEnumName}_FLAG;
#endif
`.trim()
    )
  }
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };