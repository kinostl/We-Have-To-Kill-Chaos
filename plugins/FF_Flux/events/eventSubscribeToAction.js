const id = "FF_EVENT_SUBSCRIBE_ACTION";
const groups = ["Game Specific"];
const name = "Subscribe To Action";
const actions = [
    "STORE/Initialize Stores",
    "Player/Fight",
    "Player/Shield",
    "Player/Limit Break",
    "Menu Choice/Item",
    "Menu Choice/Magic",
    "Player/Block",
    "Menu Choice/Run",
    "TURN/Take Next Turn",
    "DEFENDER/Take Damage",
    "Player/Enable",
    "Menu Choice/Choice Made",
    "MENU/Open Panel",
    "SCENE/Fade In",
    "TURN/Start Next Turn",
    "MENU/Close Panel",
    "TURN/Build Initiative",
    "REPORT/Prepare",
    "REPORT/Attack Results",
    "BLANK",
    "REPORT/Reject Menu Choice",
    "Menu Choice/Handle Choice"
];

const collator = new Intl.Collator()

const autoLabel = (fetchArg, input) => `Subscribe to ${actions[input["action"]]}`

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
  autoLabel,
  name,
  groups,
  fields,
  compile,
};