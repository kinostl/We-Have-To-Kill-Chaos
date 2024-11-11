const id = "FO_EVENT_EXPORT_SCENE_POINTER";
const groups = ["Plugins"];
const name = "Export Scene Pointer";

const fields = (
  [{
    type: "scene",
    key: "sceneId"
  }]
);


const compile = (input, helpers) => {
  const whiteSpace = /\s/g;
  const { sceneIndex, scenes, writeAsset, symbols } = helpers;
  const {sceneId} = input;
  const scene = scenes.find((x) => x.id == sceneId);
  const s_name = scene.name.replaceAll(whiteSpace, '_').toUpperCase();
  writeAsset(
    `bank_by_name_${s_name.toLowerCase()}.h`,
      /*h*/`
#ifndef FF_${s_name}_BANK
#define FF_${s_name}_BANK 
#include "${scene.symbol}.h" // IWYU pragma: export
#define ff_${s_name.toLowerCase()} ${scene.symbol}
#define ff_${s_name.toLowerCase()}_bank ((uint8_t) & __bank_${scene.symbol})
#endif
`.trim()
  )
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};