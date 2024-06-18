const id = "FF_EVENT_PROP_ACTION";
const groups = ["Game Specific"];
const name = "Propogate Action";

const fields = (
  [
    {
      label: "Informs all stores of the current action."
    },
    {
      label: "Anything placed in Update Stores will be ignored if it is not an Actor Set Position Command that targets the Player Actor."
    },
    {
      key: "currentStore",
      label: "Current Store",
      type: "variable"
    },
    {
      key: "stores",
      label: "Update Stores",
      type: "events",
    },
    {
      key: "getNextAction",
      label: "Get Next Action",
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
  const current_store = input["currentStore"]
  const stores = input["stores"].filter((x)=>(
    x.command=="EVENT_ACTOR_SET_POSITION" &&
    x.args.actorId=="$self$"
  ))
  stores.forEach((x,i)=>{
    switch_cases[i+1] = [x]
  })
  const getNextAction = input["getNextAction"]
  
  _addComment("Propogate Actions");
  caseVariableValue(current_store.id, switch_cases, getNextAction);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};