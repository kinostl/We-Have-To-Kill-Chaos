const id = "FF_EVENT_SUBSCRIBE_ACTION";
const groups = ["Game Specific"];
const name = "Subscribe To Action";
const actions = [
    "STORE/Initialize Stores",
    "Player 1/Fight",
    "Player 1/Shield",
    "Player 1/Limit Break",
    "Menu Choice/Item",
    "Menu Choice/Magic",
    "Player 1/Block",
    "Menu Choice/Run",
    "Enemy 1/Take Turn",
    "Enemy 1/Do Harm",
    "Player 1/Do Harm",
    "Menu Choice/Choice Made",
    "MENU/Open Panel",
    "SCENE/Fade In",
    "Player 1/End Turn",
    "MENU/Close Panel",
    "Enemy 1/End Turn"
];

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "action",
      type: "select",
      defaultValue: 0,
      options: actions.map((x, i)=>[i, x]).sort((a,b)=>collator.compare(a[1],b[1]))
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
    variablesLookup,
    _addComment
  } = helpers;
  const var_action = Object.values(variablesLookup).find((x)=>x.name=="Action")

  ifVariableValue(
    var_action.id,
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