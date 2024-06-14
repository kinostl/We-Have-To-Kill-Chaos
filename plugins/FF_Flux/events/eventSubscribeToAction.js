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
    "TURN/Roll Initiative",
    "REPORT/Reject Menu Choice",
    "Menu Choice/Handle Choice",
    "TURN/Sort Initiative"
];

const autoLabel = (fetchArg, input) => `Subscribe to ${actions[input["action"]]}`

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
    _addComment,
    additionalOutput,
    entity,
    entityIndex
  } = helpers;
  const var_action = Object.values(variablesLookup).find((x)=>x.name=="Action")
  if (!additionalOutput['dat_chart']) {
    additionalOutput['dat_chart'] = {
      filename: 'dat_chart.md',
      data: `a${input["action"]}(${actions[input["action"]]})-.->${entity.id}[(${entity.name})]\n`
    }
  } else {
    additionalOutput['dat_chart'].data = `a${input["action"]}(${actions[input["action"]]})-.->${entity.id}[(${entity.name})]\n` + additionalOutput['dat_chart'].data
  }

  _addComment(`Subscribe to: ${actions[input["action"]]}`)
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