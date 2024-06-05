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
    "Enemy 1/Take Turn",
    "Enemy 1/Do Harm",
    "Player 1/Do Harm",
    "MENU/Choice Made"
];

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

//[{"command":"EVENT_SET_VALUE","args":{"variable":"0","value":{"type":"number","value":20}},"id":"dcf56a52-8db5-48b3-8d41-fb50433e01b9"}]

const getEvent = (variable, value) => {
  const event = {
    "command": "EVENT_SET_VALUE",
      "args": {
      "variable": `${variable}`,
        "value": {
        "type": "number",
          "value": `${value}`
      }
    },
    "id": `${variable}-set-to-${value}`
  }

  return event
}

const actionOverflowError = {
  "command": "EVENT_TEXT",
  "args": {
    "text": ["Error: Action \nStack Overflow"],
    "avatarId": ""
  },
  "id": "report-action-stack-overflow"
}

const compile = (input, helpers) => {
  const {
    variablesLookup,
    _addComment,
    _addNL,
    variableInc,
    caseVariableValue
  } = helpers;

  const stack_ptr = Object.values(variablesLookup).find((x)=>x.name=="Action/Stack Pointer")
  if(!stack_ptr) {
    throw new Error(`Variable Not Found: Action/Stack Pointer`)
  }
  const switch_cases = {}
  
  Array(16).fill(0).forEach((x, i)=>{
    const find_slot = `Action/Stack ${i + 1}`
    const stack_slot = Object.values(variablesLookup).find((x)=>x.name==find_slot)
    if(!stack_slot) {
      throw new Error(`Variable Not Found: ${find_slot}`)
    }
    switch_cases[i] = [getEvent(stack_slot.id, input["action"])]
  })

  _addComment(`Dispatch: ${actions[input["action"]]}`);
  caseVariableValue(stack_ptr.id, switch_cases, [actionOverflowError]);

  variableInc(stack_ptr.id);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};