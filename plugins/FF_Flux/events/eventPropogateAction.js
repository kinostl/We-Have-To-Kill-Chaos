const id = "FF_EVENT_PROP_ACTION";
const groups = ["Game Specific"];
const name = "Propogate Action";

const fields = (
  [
    {
      key: "stores",
      label:"Update Stores",
      type: "events",
    },
    {
      key: "updateView",
      label: "Update Views",
      type: "events"
    }
  ]
);

const clearSlot = (variable) => {
  const randomId = ()=>`${Math.random().toString(16).slice(2)}`
  
  const event = {
    "command": "EVENT_SET_VALUE",
      "args": {
      "variable": `${variable}`,
        "value": {
        "type": "number",
          "value": '0'
      }
    },
    "id": `${randomId()}`
  }

  return event
}

const compile = (input, helpers) => {
  const {
    _addComment,
    _addNL,
    caseVariableValue,
    variableInc,
    variablesLookup,
    getVariableAlias
  } = helpers;

  const switch_cases = {}
  const current_store = Object.values(variablesLookup).find((x) => x.name == "Action/Current Store")
  const stores = input["stores"]
  stores.forEach((x,i)=>{
    switch_cases[i] = [x]
  })
  const updateView = input["updateView"]
  updateView.unshift(clearSlot(current_store.id))
  
  _addComment("Propogate Actions");
  variableInc(current_store.id);
  caseVariableValue(current_store.id, switch_cases, updateView);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};