const id = "FO_EVENT_SUBMAP2";
const groups = ["Plugins"];
const name = "BKG SubMap";

const numberOpts = Array(8).fill(0).map((x,i)=>[i,`${i+1}`])

const fields = (
  [
    {
      key: "keyX",
      label: "X",
      type: "value",
      defaultValue: {type:"number",value:"0"},
      width: "50%",
    },
    {
      key: "keyY",
      label: "Y",
      type: "value",
      defaultValue: {type:"number",value:"0"},
      width: "50%",
    },
    {
      type: "break",
    },
    {
      key: "keyW",
      label: "W",
      type: "value",
      defaultValue: {type:"number",value:"1"},
      width: "50%",
    },
    {
      key: "keyH",
      label: "H",
      type: "value",
      defaultValue: {type:"number",value:"1"},
      width: "50%",
    },
    {
      type: "break",
    },
    {
      key: "keySX",
      label: "SX",
      type: "value",
      defaultValue: {type:"number",value:"0"},
      width: "50%",
    },
    {
      key: "keySY",
      label: "SY",
      type: "value",
      defaultValue: {type:"number",value:"0"},
      width: "50%",
    },
    {
      key:"color",
      label:"Color",
      type:"union",
      types: ["value", "togglebuttons"],
      defaultType: "togglebuttons",
      defaultValue: {
        togglebuttons: 0,
        value: 0
      },
      options:numberOpts
    },
  ]
);

const compile = (input, helpers) => {
  const {
    _callNative,
    _stackPush,
    _stackPushConst,
    _stackPop,
    variableSetToUnionValue,
    _declareLocal
  } = helpers;
  const localVariable = _declareLocal("fo_event_submap2", 1, true)

  if (input.color.type == "togglebuttons") {
    _stackPushConst(input.color.value);
  } else {
    variableSetToUnionValue(localVariable, input.color.value)
    _stackPush(localVariable)
  }
  ["keyX", "keyY", "keyW", "keyH", "keySX", "keySY"]
    .forEach((x) => {
      variableSetToUnionValue(localVariable, input[x])
      _stackPush(localVariable)
    })

  _callNative('copyBkgToBkg');

  _stackPop(7);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };