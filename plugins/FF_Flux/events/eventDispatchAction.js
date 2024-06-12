const id = "FF_EVENT_DISPATCH_ACTION";
const groups = ["Game Specific"];
const name = "Dispatch Action";
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

const autoLabel = (fetchArg, input) => `Dispatch: ${actions[input["action"]]}`

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "action",
      type: "select",
      defaultValue: 0,
      options: actions.map((x, i)=>[i, x]).sort((a,b)=>collator.compare(a[1],b[1]))
    }
  ]
);

const compile = (input, helpers) => {
  const {
    variablesLookup,
    _addComment,
    _addNL,
    _setInd,
    variableInc,
    getNextLabel,
    _ifConst,
    _jump,
    _label,
    _string,
    _displayText,
    _loadText,
    _stackPushConst,
    _stackPop,
    getVariableAlias
  } = helpers;

  const stack_ptr = Object.values(variablesLookup).find((x) => x.name == "Action/End Of Stack")
  const stack_ptr_alias = getVariableAlias(stack_ptr.id)
  if (!stack_ptr) {
    throw new Error(`Variable Not Found: Action/End Of Stack`)
  }

  _addComment(`Dispatch: ${actions[input["action"]]}`)
  _addComment(JSON.stringify(stack_ptr))

  const trueLabel = getNextLabel()
  const endLabel = getNextLabel()
  _ifConst(".LTE", stack_ptr.id, (9 + 16), trueLabel, 0)
  _loadText(0)
  _string("Error: Action \\nStack Overflow")
  _displayText()
  _jump(endLabel)
  _label(trueLabel)
  _stackPushConst(input["action"])
  _setInd(stack_ptr_alias, ".ARG0")
  _stackPop(1)
  variableInc(stack_ptr.id)
  _label(endLabel)

  _addNL();
};

module.exports = {
  id,
  autoLabel,
  name,
  groups,
  fields,
  compile,
};