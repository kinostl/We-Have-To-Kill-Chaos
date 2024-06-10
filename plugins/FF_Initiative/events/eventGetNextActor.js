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
    _label,
    _setInd
  } = helpers;

  const _getVarAlias = (var_name)=>{
    return getVariableAlias(
      Object.values(variablesLookup)
        .find((x) => x.name == var_name).id
    )
  }
  _addComment("Set Next Actor")
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
  const max_value = _getVarAlias("Turn Order/Max Value")
  const max_value_ptr = _getVarAlias("Turn Order/Max Value Ptr")
  const current_actor = _getVarAlias("Turn Order/Current Actor")

  _setConst(current_actor, 0)

  turn_slots.forEach(
    (slot, i) => {
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
      _setConst(max_value_ptr, slot)
      _setConst(current_actor, i+1)
      _label(endLabel)
      _stackPop(1)
    }
  )

  _stackPushConst(0)
  _setInd(max_value_ptr, ".ARG0")
  _stackPop(1)

  _setConst(max_value, 0)

  _addNL()
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};