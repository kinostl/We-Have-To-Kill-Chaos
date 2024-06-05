const id = "FF_EVENT_DISPATCH_ACTION";
const groups = ["Game Specific"];
const name = "Dispatch Action";
const actions = [
    "STORE/Initialize Stores",
    "Player 1/Fight",
    "Player 1/Shield",
    "Player 1/Limit Break",
    "MENU/Item",
    "MENU/Magic",
    "Player 1/Block",
    "MENU/Run",
    "Enemy 1/Take Turn"
];


const fields = (
  [
    {
      key: "action",
      type: "select",
      defaultValue: 0,
      options: actions.map((x, i)=>[i, x])
    }
  ]
);

const compile = (input, helpers) => {
  const {
    appendRaw,
    _addComment,
    _addNL
  } = helpers;

  _addComment(`Dispatch: ${actions[input["action"]]}`);
  appendRaw(`VM_SET_CONST VAR_ACTION, ${input["action"]}`);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};