const id = "MY_EVENT_CALL_NATIVE"
const groups = ["Native Helper"]
const name = "Call Native"

MAX_STACK_SIZE = 8

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
    _stackPush,
    _stackPop,
    _callNative,
    _declareLocal,
    _markLocalUse
  } = helpers

  _addComment(`Call Native: ${input['funName']}`)
  const valHolder = _declareLocal(`my_event_call_native_val`, 1, true);
  if (input.argCount > 0) {
    for (let i = 0; i < input.argCount; i++) {
      variableSetToScriptValue(valHolder, input[`arg${i}`]);
      _stackPush(valHolder)
    }
  }

  _callNative(input.funName)

  if (input.argCount > 0) {
    _stackPop(input.argCount)
  }
  _markLocalUse(valHolder)
}

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
}
