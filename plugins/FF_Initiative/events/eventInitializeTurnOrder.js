const id = "FF_EVENT_INIT_TURN_QUEUE";
const groups = ["Game Specific"];
const name = "Initialize Turn Order Queue";

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Clears Turn Order Queue to -1"
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

  const _getVarAlias = (var_name)=>{
    return getVariableAlias(
      Object.values(variablesLookup)
        .find((x) => x.name == var_name).id
    )
  }

  const turn_slots = Object.values(variablesLookup)
    .filter((x) => x.name.startsWith("Turn Order/Slot"))
    .map((x)=>{
      const asArr = x.name.split(/[/ #]/)
      x.sortOrder = Number(asArr[3])
      return x
    })
    .sort((a, b)=> {
      return a.sortOrder - b.sortOrder
    })
    .map((x) => getVariableAlias(x.id))
  const current_actor = _getVarAlias("Turn Order/Current Actor")

  _addComment(`Initialize Turn Slots`);
  turn_slots.forEach((x)=>{
    _setConst(x, -1)
  })
  _setConst(current_actor, -1)
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};