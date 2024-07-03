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
       type: "union",
       types: ["number", "variable", "actor"],
       defaultType: "number",
         defaultValue: {
           number: 0,
       variable: "LAST_VARIABLE",
         },
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
    _callNative,
    _stackPushConst,
    _stackPush,
    _stackPop,
    getActorIndex,
    getVariableAlias
  } = helpers
  
  const pushUnion = (union) => {
    switch(union.type){
      case "number":
        _stackPushConst(union.value)
        break;
      case "variable":
        _stackPush(getVariableAlias(union.value))
        break;
      case "actor":
        _stackPushConst(
          getActorIndex(union.value)
        )
        break;
    }
  }
  
  if(input.argCount > 0){
    for(let i=0; i<input.argCount; i++){
      pushUnion(input[`arg${i}`])
    }
  }
  
  _callNative(input.funName)
  
  if(input.argCount > 0){
    _stackPop(input.argCount)
  }
}

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
}
