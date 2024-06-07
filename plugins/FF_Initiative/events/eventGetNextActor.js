const id = "FF_EVENT_SET_NEXT_TURN";
const groups = ["Game Specific"];
const name = "Set Next Turn";

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
    _ifConst,
    _stackPushConst,
    _stackPop,
    _rpn,
    _addComment,
    _addNL,
    _setConst,
    getVariableAlias,
    getNextLabel,
    _jump,
    _label
  } = helpers;

  _addComment("Set Next Actor")
  const turn_slots = Object.values(variablesLookup).filter((x) => x.name.startsWith("Turn Order/Slot")).map((x)=>getVariableAlias(x.id))
  const max_value = getVariableAlias(Object.values(variablesLookup).find((x)=>x.name == "Turn Order/Max Value").id)
  const next_actor = getVariableAlias(Object.values(variablesLookup).find((x)=>x.name == "Turn Order/Next Actor").id)

  turn_slots.forEach(
    (slot) => {
      _stackPushConst(0)
      const set_max = _rpn()
      set_max.ref(max_value)
      set_max.ref(slot)
      set_max.operator('.MAX')
      set_max.refSet(max_value)
      set_max.ref(max_value)
      set_max.ref(slot)
      set_max.operator('.EQ')
      set_max.refSet(".ARG0")
      set_max.stop()

      const trueLabel = getNextLabel()
      const endLabel = getNextLabel()
      _ifConst(".GT", ".ARG0", 0, trueLabel, 0)
      _jump(endLabel)
      _label(trueLabel)
      _setConst(next_actor, slot)
      _label(endLabel)
      _stackPop(1)
    }
  )

  _addNL()
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};