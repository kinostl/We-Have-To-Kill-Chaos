const id = "FF_EVENT_DISPATCH_ACTION";
const groups = ["Game Specific"];
const name = "Dispatch Action";

const actions = [
    "ANIMATE/Explosions",
    "ATTACKER/Fight",
    "ANIMATE/Flash Enemy",
    "Player/Limit Break",
    "PICK/Item",
    "PICK/Magic",
    "Player/Block",
    "PICK/Run",
    "ATTACKER/Take Next Turn",
    "DEFENDER/Take Damage",
    "PICK/Enable Player",
    "PICK/Choice Made",
    "PANEL/Display Menu",
    "SCENE/Fade In",
    "ATTACKER/Start Next Turn",
    "PANEL/Close Panel",
    "TURN/Build Initiative",
    "REPORT/Prepare",
    "REPORT/Attack Results",
    "TURN/Roll Initiative",
    "REPORT/Reject Menu Choice",
    "PICK/Handle Choice",
    "TURN/Sort Initiative",
    "PANEL/Display Party",
    "PANEL/Open Panel",
    "PANEL/Display Current Actor",
    "PANEL/Display Party Actors",
    "PANEL/Hide Current Actor",
    "PANEL/Hide Party Actors"
];

const autoLabel = (fetchArg, input) => `Dispatch: ${actions[input["action"]]}`

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "action",
      type: "select",
      defaultValue: 0,
      options: actions.map((x, i)=>[i, `${x} (${i})`]).sort((a,b)=>collator.compare(a[1],b[1]))
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
    getVariableAlias,
    additionalOutput,
    entity,
    entityIndex
  } = helpers;

  // if (!additionalOutput['dat_chart']) {
  //   additionalOutput['dat_chart'] = {
  //     filename: 'dat_chart.md',
  //     data: `${entity.id}[(${entity.name})]-->a${input["action"]}(${actions[input["action"]]})\n`
  //   }
  // } else {
  //   additionalOutput['dat_chart'].data += `${entity.id}[(${entity.name})]-->a${input["action"]}(${actions[input["action"]]})\n`
  // }

  const stack_ptr = Object.values(variablesLookup).find((x) => x.name == "Action/End Of Stack")
  const stack_ptr_alias = getVariableAlias(stack_ptr.id)
  if (!stack_ptr) {
    throw new Error(`Variable Not Found: Action/End Of Stack`)
  }

  _addComment(`Dispatch: ${actions[input["action"]]}`)

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