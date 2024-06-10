const id = "FF_EVENT_INIT_ACTION_QUEUE";
const groups = ["Game Specific"];
const name = "Initialize Action Queue";

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Clears Action Queue to -1"
    }
  ]
);

const compile = (input, helpers) => {
  const {
    variablesLookup,
    _addComment,
    _addNL,
    getVariableAlias,
    _setConst
  } = helpers;

  const action_slots = Object.values(variablesLookup)
  .filter((x) => x.name.startsWith("Action/Stack"))
  .map((x)=>getVariableAlias(x.id))

  if(action_slots.length != 16){
    throw new Error(`Action Stack Wrong Size: ${action_slots.length}`)
  }

  const stack_ptr = Object.values(variablesLookup).find((x) => x.name == "Action/End Of Stack")
  const stack_ptr_alias = getVariableAlias(stack_ptr.id)
  if (!stack_ptr) {
    throw new Error(`Variable Not Found: Action/End Of Stack`)
  }

  const action = Object.values(variablesLookup).find((x) => x.name == "Action")
  const action_alias = getVariableAlias(action.id)
  const queue_ptr = Object.values(variablesLookup).find((x) => x.name == "Action/Queue Pointer")
  const queue_ptr_alias = getVariableAlias(queue_ptr.id)

  if (!action) {
    throw new Error(`Variable Not Found: Action`)
  }
  if (!queue_ptr) {
    throw new Error(`Variable Not Found: Action/Queue Pointer`)
  }

  _addComment(`Initialize Actions`);
  action_slots.forEach((x)=>{
    _setConst(x, -1)
  })
  _setConst(action_alias, -1)
  _setConst(stack_ptr_alias, 9)
  _setConst(queue_ptr_alias, 9)
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};