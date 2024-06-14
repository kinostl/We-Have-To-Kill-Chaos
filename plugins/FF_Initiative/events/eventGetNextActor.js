const id = "FF_EVENT_SET_NEXT_TURN";
const groups = ["Game Specific"];
const name = "Set Next Turn";
const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Sets Next Actor to the highest Turn Slot value Indirectly"
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

  const _getVarAlias = (var_name) => {
    return getVariableAlias(
      Object.values(variablesLookup)
        .find((x) => x.name == var_name).id
    )
  }
  const turn_slots = Object.values(variablesLookup)
    .filter((x) => x.name.startsWith("Turn Order/Slot"))
    .map((x) => {
      const asArr = x.name.split(/[/ #]/)
      x.sortOrder = Number(asArr[3])
      return x
    })
    .sort((a, b) => {
      return a.sortOrder - b.sortOrder
    })
    .map((x) => getVariableAlias(x.id))

  const current_actor = _getVarAlias("Turn Order/Current Actor")

  const next_in_line = turn_slots[0]
  const copy_start = turn_slots[1]
  const copy_end = turn_slots[9]

  _addComment(`Get Next Actor`);

  _set(current_actor, next_in_line);
  _memCpy(next_in_line, copy_start, 9);
  _setConst(copy_end, -1);
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};