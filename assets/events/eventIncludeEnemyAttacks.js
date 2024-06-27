const id = "FF_EVENT_MAKE_ENEMY_ATTACK";
const groups = ["Game Specific"];
const name = "Include Enemy Attacks";

const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Provides Enemy Attack GBVM Macros"
    }
  ]
);

const compile = (input, helpers) => {
  const {
    _includeHeader
  } = helpers;
  _includeHeader("attacks.s")
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};
