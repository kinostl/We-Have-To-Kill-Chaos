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
    _set,
    variableDec,
    getVariableAlias,
    _memCpy,
    _setConst
  } = helpers;

  const action = Object.values(variablesLookup).find((x) => x.name == "Action")
  const action_alias = getVariableAlias(action.id)

  const next_in_line = Object.values(variablesLookup).find((x)=>x.name == "Action/Stack 1")
  const next_in_line_alias = getVariableAlias(next_in_line.id)

  const copy_start = Object.values(variablesLookup).find((x)=>x.name == "Action/Stack 2")
  const copy_start_alias = getVariableAlias(copy_start.id)

  const end_of_line = Object.values(variablesLookup).find((x) => x.name == "Action/End Of Stack")

  const copy_end = Object.values(variablesLookup).find((x)=>x.name == "Action/Stack 16")
  const copy_end_alias = getVariableAlias(copy_end.id)

  if (!action) {
    throw new Error(`Variable Not Found: Action`)
  }
  if (!end_of_line) {
    throw new Error(`Variable Not Found: Action/End Of Stack`)
  }
  if (!next_in_line) {
    throw new Error(`Variable Not Found: Action/Stack 1`)
  }
  if (!copy_start) {
    throw new Error(`Variable Not Found: Action/Stack 2`)
  }

  _addComment(`Dequeue Action`);
  
  _set(action_alias, next_in_line_alias);
  _memCpy(next_in_line_alias, copy_start_alias, 15);
  _setConst(copy_end_alias, -1);
  variableDec(end_of_line.id);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};