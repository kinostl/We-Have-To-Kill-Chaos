const id = "FO_EVENT_SUBFLASH";
const groups = ["Plugins"];
const name = "Make BKG Flash";

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
      key:"color1",
      label:"Color 1",
      type:"togglebuttons",
      options:numberOpts
    },
    {
      key:"color2",
      label:"Color 2",
      type:"togglebuttons",
      options:numberOpts
    }
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

    _stackPushConst(input.color1);
    _stackPushConst(input.color2);

    _stackPushConst(input.keyX);
    _stackPushConst(input.keyY);
    
    _stackPushConst(input.keyW);
    _stackPushConst(input.keyH);

    _callNative('makeBkgFlash');
    
    _stackPop(6);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };