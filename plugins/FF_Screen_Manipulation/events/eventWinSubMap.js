
const id = "FO_EVENT_SUBMAP1";
const groups = ["Plugins"];
const name = "SubMap";

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
    }
  ]
);

const compile = (input, helpers) => {
    const { 
        _callNative,
        _stackPushConst,
        _stackPop,
        _declareLocal,
        _setConst,
        appendRaw

    } = helpers;

    _stackPushConst(input.keyX);
    _stackPushConst(input.keyY);
    
    _stackPushConst(input.keyW);
    _stackPushConst(input.keyH);

    _stackPushConst(input.keySX);
    _stackPushConst(input.keySY);

    //_callNative('copyBkgToWin');
    appendRaw('VM_OVERLAY_SET_SUBMAP_EX .ARG5');
    
    _stackPop(6);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };