const id = "FF_EVENT_POP_ACTION";
const groups = ["Game Specific"];
const name = "Pop Action";

const collator = new Intl.Collator()


const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Removes an Action from the end of the Action Stack and assigns it to Action"
    }
  ]
);

// [{"command":"EVENT_SET_VALUE","args":{"variable":"L0","value":{"type":"variable","value":"L0"}},"id":"5dc1180e-32d0-4951-a70d-c7009dda49e8"}]

const getEvent = (var_a, var_b) => {
  const event = {
    "command": "EVENT_SET_VALUE",
    "args": {
      "variable": var_a,
      "value": {
        "type": "variable",
        "value": var_b
      }
    },
    "id": `set-${var_a}-to-${var_b}`
  }
  return event
}

const actionStackMissingError = {
  "command": "EVENT_TEXT",
  "args": {
    "text": ["Error: Action \nSlot Not Found"],
    "avatarId": ""
  },
  "id": "report-action-stack-missing"
}

const stopActionPop = {
  "command": "EVENT_STOP",
  "args": {},
  "id": "stop-pop-action-stack"
}
const clearSlot = (variable) => {
  const event = {
    "command": "EVENT_SET_VALUE",
      "args": {
      "variable": `${variable}`,
        "value": {
        "type": "number",
          "value": '-1'
      }
    },
    "id": `clear-${variable}`
  }

  return event
}

const compile = (input, helpers) => {
  const {
    variablesLookup,
    _addComment,
    _addNL,
    ifVariableValue,
    variableDec,
    caseVariableValue
  } = helpers;

  const action = Object.values(variablesLookup).find((x) => x.name == "Action")
  const stack_ptr = Object.values(variablesLookup).find((x) => x.name == "Action/Stack Pointer")
  if (!action) {
    throw new Error(`Variable Not Found: Action`)
  }
  if (!stack_ptr) {
    throw new Error(`Variable Not Found: Action/Stack Pointer`)
  }


  const switch_cases = {}

  Array(16).fill(0).forEach((x, i) => {
    const find_slot = `Action/Stack ${i + 1}`
    const stack_slot = Object.values(variablesLookup).find((x) => x.name == find_slot)
    if (!stack_slot) {
      throw new Error(`Variable Not Found: ${find_slot}`)
    }
    switch_cases[i] = [getEvent(action.id, stack_slot.id)]
  })


  _addComment(`Pop Action`);
  variableDec(stack_ptr.id);
  caseVariableValue(stack_ptr.id, switch_cases, [actionStackMissingError]);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};