const id = "MY_EVENT_CALL_NATIVE"
const groups = ["Native Helper"]
const name = "Call Native"

MAX_STACK_SIZE = 8
const autoLabel = (fetchArg, input) => `${name}: ${input["funName"]}`

const fields = [
  {
    key: "funName",
    label: "Native Function Name",
    type: "text",
    placeholder: "handleEvent"
  },
  {
    key:"argCount",
    label:"Argument Count",
    type: "number",
    defaultValue: 0,
      min: 0,
      max: 8
  },
  ...Array(MAX_STACK_SIZE)
  .fill()
  .map((x, i)=>{
    return {
      key: `arg${i}`,
       label: `Argument #${i+1}`,
       type: "value",
       conditions: [
         {
           key: "argCount",
       gte: i+1,
         }
       ],
    }
  })
]

const compile = (input, helpers) => {
  const {
    _addComment,
    variableSetToScriptValue,
    getVariableAlias,
    _set,
    _stackPush,
    _stackPop,
    _callNative,
    _declareLocal,
    _markLocalUse
  } = helpers

  _addComment(`Call Native: ${input['funName']}`)
  const valHolders = Array(input.argCount).fill(0).map((x,idx)=>{
    return _declareLocal(`my_event_call_native_val_${idx}`, 1, true);
  })

  if (input.argCount > 0) {
    for (let i = input.argCount - 1; i >= 0; i--) {
      variableSetToScriptValue(valHolders[i], input[`arg${i}`]);
      _stackPush(valHolders[i])
    }
  }

  _callNative(input.funName)

  for(let i=0;i<input.argCount;i++){
    if(input[`arg${i}`].type == "variable"){
      const vRef = getVariableAlias(input[`arg${i}`].value)
      _set(vRef, ".ARG0");
    }
    _stackPop(1)
    _markLocalUse(valHolders[i])
  }
}

module.exports = {
  id,
  name,
  autoLabel,
  groups,
  fields,
  compile,
}
