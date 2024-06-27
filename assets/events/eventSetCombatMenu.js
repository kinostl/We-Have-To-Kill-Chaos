
const id = "FF_EVENT_SET_COMBAT_MENU";
const groups = ["Game Specific"];
const name = "Update Combat Menu";

const sub_fields = (_key) => ([
      {
        key: `slot_${_key}_name`,
        type: "text",
        defaultValue: ""
      },
      {
        key: `slot_${_key}_cost`,
        type: "number",
        defaultValue: 0,
        width: "25%"
      }
    ])
const sub_fields_2 = (_key) => ([
  {
    key: `slot_${_key}_name`,
    type: "text",
    defaultValue: ""
  },
])

const fields = (
  [
    {type:"group", key:"slot_1", fields: sub_fields(1)},
    {type:"group", key:"slot_2", fields: sub_fields(2)},
    {type:"group", key:"slot_3", fields: sub_fields(3)},
    {type:"group", key:"slot_4", fields: sub_fields(4)},
    {type:"group", key:"slot_5", fields: sub_fields_2(5)},
    {type:"group", key:"slot_6", fields: sub_fields_2(6)},
    {type:"group", key:"slot_7", fields: sub_fields_2(7)},
    {type:"group", key:"slot_8", fields: sub_fields_2(8)}
  ]
);

const compile = (input, helpers) => {
  const {
    _loadText,
    _string,
    _displayText,
    _overlayWait,
    _addComment
  } = helpers;

  const str_1 = [
    "slot_1",
    "slot_2",
    "slot_3",
    "slot_4",
  ].map((i)=>{
    const _name = input[`${i}_name`].slice(0, 6).padEnd(6)
    const _cost = input[`${i}_cost`]
    let _cost_display = ""
    if(_cost > 0) {
      _cost_display = Array(_cost).fill("+").join("").padEnd(6, " ")
    }else if(_cost < 0){
      _cost_display = Array(_cost * - 1).fill("-").join("").padEnd(6, " ")
    }else if(_cost === 0){
      _cost_display = _cost_display.padEnd(6, " ")
    }
    return `${_name}\\n${_cost_display}`
  })

  const str_2 = [
    "slot_5",
    "slot_6",
    "slot_7",
    "slot_8"
  ].map((i)=>{
    return input[`${i}_name`].slice(0, 6).padEnd(6)
  })

  const str = str_1.concat(str_2).join("\\n")
  _loadText(0)
  _string(`\\001\\1\\003\\2\\6${str}`)
  _displayText()
  _overlayWait(true, [".UI_WAIT_TEXT"])
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};