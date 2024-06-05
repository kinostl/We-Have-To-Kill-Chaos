const id = "FF_EVENT_SUBSCRIBE_ACTION";
const groups = ["Game Specific"];
const name = "Subscribe To Action";
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
    },
    {
      key: "response",
      type: "events"
    }
  ]
);

const compile = (input, helpers) => {
  const {
    ifVariableValue,
  } = helpers;

  // 00 is VAR_ACTION
  ifVariableValue(
    '00',
    '.EQ',
    `${input["action"]}`,
    input["response"]
  )
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};