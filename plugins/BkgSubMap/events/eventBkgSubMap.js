const id = "FO_EVENT_SUBMAP2";
const groups = ["Plugins"];
const name = "BKG SubMap";

const numberOpts = Array(8).fill(0).map((x,i)=>[i,`${i+1}`])

const fields = (
  [
    {
      key: "keyX",
      label: "X",
      type: "number",
      defaultValue: 0,
      width: "50%",
    },
    {
      key: "keyY",
      label: "Y",
      type: "number",
      defaultValue: 0,
      width: "50%",
    },
    {
      type: "break",
    },
    {
      key: "keyW",
      label: "W",
      type: "number",
      defaultValue: 1,
      width: "50%",
    },
    {
      key: "keyH",
      label: "H",
      type: "number",
      defaultValue: 1,
      width: "50%",
    },
    {
      type: "break",
    },
    {
      key: "keySX",
      label: "SX",
      type: "number",
      defaultValue: 0,
      width: "50%",
    },
    {
      key: "keySY",
      label: "SY",
      type: "number",
      defaultValue: 0,
      width: "50%",
    },
    {
      key:"color",
      label:"Color",
      type:"togglebuttons",
      options:numberOpts
    },
  ]
);

const compile = (input, helpers) => {
    const { 
        _callNative,
        _stackPushConst,
        _stackPop,
        backgrounds,
        scene,
        appendRaw
    } = helpers;

    _stackPushConst(input.color);
    _stackPushConst(input.keyX);
    _stackPushConst(input.keyY);
    
    _stackPushConst(input.keyW);
    _stackPushConst(input.keyH);

    _stackPushConst(input.keySX);
    _stackPushConst(input.keySY);

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