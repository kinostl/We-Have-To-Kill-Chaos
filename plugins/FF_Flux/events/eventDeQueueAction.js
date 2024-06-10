const id = "FF_EVENT_DEQUEUE_ACTION";
const groups = ["Game Specific"];
const name = "Dequeue Action";

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Removes an Action from the start of the Action Stack and assigns it to Action"
    }
  ]
);

const compile = (input, helpers) => {
  const {
    variablesLookup,
    _addComment,
    _addNL,
    _getInd,
    variableInc,
    getVariableAlias
  } = helpers;

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

  _addComment(`Dequeue Action`);
  _getInd(action_alias, queue_ptr_alias)
  variableInc(queue_ptr.id);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};