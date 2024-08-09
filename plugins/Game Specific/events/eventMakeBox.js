const id = "FF_EVENT_MAKE_BOX";
const groups = ["Game Specific"];
const name = "Make a Box";


const fields = (
  [
    {
        type: "value",
        label: "X",
        key: "x"
    },
    {
        type: "value",
        label: "Y",
        key: "y"
    },
    {
        type: "value",
        label: "W",
        key: "w"
    },
    {
        type: "value",
        label: "H",
        key: "h"
    }
  ]
);


const compile = (input, helpers) => {
    const {
        _addComment,
        variableSetToScriptValue,
        _stackPush,
        _stackPop,
        _callNative,
        _declareLocal,
        _markLocalUse
    } = helpers;
    const ins = [input.x, input.y, input.w, input.h]
    _addComment('Draw A Box')
    const valHolder = _declareLocal(`ff_make_box_val`, 1, true);
    ins.reverse().forEach((i) => {
        variableSetToScriptValue(valHolder, i);
        _stackPush(valHolder)
    });
    _callNative('makeBox')
    _stackPop(4)
    _markLocalUse(valHolder)
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};