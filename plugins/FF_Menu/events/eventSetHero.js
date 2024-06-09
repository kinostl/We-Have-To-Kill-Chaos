const id = "FF_EVENT_SET_HERO";
const groups = ["Game Specific"];
const name = "Update HERO";

const fields = (
  [
    {
      key: "name",
      type: "text",
      defaultValue: "",
      maxLength: 6
    },
    {
      key: "hp",
      type: "variable",
      defaultValue: "LAST_VARIABLE",
    },
    {
      key: "ap",
      type: "variable",
      defaultValue: "LAST_VARIABLE",
    }
  ]
);

const randomId = ()=>`${Math.random().toString(16).slice(2)}`

// If you're reading this, I got this by just making a type of event, 
// and then using _addComment(JSON.stringify()) to get this.
// It is not documented anywhere as far as I can tell.
const makeStarEvent = (iter_val, star_ref, ap_val, id) => ({
    "command": "EVENT_IF",
    "args": {
      "condition": {
        "type": "lt",
        "valueA": {
          "type": "number",
          "value": iter_val
        },
        "valueB": {
          "type": "variable",
          "value": ap_val
        }
      },
      "__collapseElse": false
    },
    "children": {
      "true": [{
        "command": "EVENT_SET_VALUE",
        "args": {
          "variable": star_ref,
          "value": {
            "type": "number",
            "value": "+".charCodeAt(0)
          },
          "__collapse": true
        },
        "id": `${id}_true`
      }],
      "false": [{
        "command": "EVENT_SET_VALUE",
        "args": {
          "variable": star_ref,
          "value": {
            "type": "number",
            "value": "-".charCodeAt(0)
          },
          "__collapse": true
        },
        "id": `${id}_false`
      }]
    },
    "id": `${id}_if`
  })

const compile = (input, helpers) => {
  const {
    _loadText,
    _string,
    _displayText,
    _overlayWait,
    getVariableAlias,
    _addComment,
    _dw,
    compileEvents,
    variablesLookup
  } = helpers;
  _addComment('Draw Stars')
  const _name = input["name"].slice(0,6).padEnd(6, ' ')
  const hero_hp = getVariableAlias(input["hp"])
  const hero_ap = input["ap"]

  const starRef = Object.values(variablesLookup)
    .filter((x) => x.name.endsWith("#C"))
    .map((x)=>{
      const asArr = x.name.split(/#/)
      x.sortOrder = Number(asArr[0])
      return x
    })
    .sort((a, b)=> {
      return a.sortOrder - b.sortOrder
    })
    .slice(0,6)
  const starRefId = starRef.map((x) => x.id)
  const starRefAlias = starRef.map((x) => getVariableAlias(x.id))
  const starEvents = starRefId.map((x,i)=>makeStarEvent(i, x, hero_ap, randomId()))

  compileEvents(starEvents)

  _loadText(7)
  _dw([hero_hp, ...starRefAlias])
  _string(`\\001\\1\\003\\2\\2${_name}\\003\\5\\3%D3\\003\\5\\4%c%c%c\\n%c%c%c`)
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

/*
; Variable Set To
VM_SET_CONST            VAR_S2_LOCAL_0, 0

2$:
; If Variable .LT Value
; -- Calculate value
VM_RPN
    .R_REF      VAR_PLAYER_1_AP
    .R_REF_SET  .LOCAL_TMP0_IF_VALUE
    .R_STOP
VM_IF                   .LT, VAR_S2_LOCAL_0, .LOCAL_TMP0_IF_VALUE, 3$, 0
VM_JUMP                 4$
3$:

VM_PUSH_CONST '+'

; Variables .ADD
VM_RPN
    .R_REF      VAR_S2_LOCAL_0
    .R_INT16    1
    .R_OPERATOR .ADD
    .R_REF_SET  VAR_S2_LOCAL_0
    .R_STOP

VM_JUMP                 2$
4$:

; Variable Set To
VM_SET                  VAR_S2_LOCAL_0, VAR_PLAYER_1_AP

6$:
; If Variable .LTE Value
VM_IF_CONST             .LTE, VAR_S2_LOCAL_0, 6, 7$, 0
VM_JUMP                 8$
7$:

VM_PUSH_CONST '-'

; Variables .ADD
VM_RPN
    .R_REF      VAR_S2_LOCAL_0
    .R_INT16    1
    .R_OPERATOR .ADD
    .R_REF_SET  VAR_S2_LOCAL_0
    .R_STOP

VM_JUMP                 6$
8$:

VM_POP 6
*/


