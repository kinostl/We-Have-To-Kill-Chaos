const id = "FF_EVENT_SET_HERO";
const groups = ["Game Specific"];
const name = "Update HERO";

const fields = (
  [
    {
      type: "label",
      label: "Sets up the MENU for the current player"
    },
  ]
);


const compile = (input, helpers) => {
  const {
    _displayText,
    _overlayWait,
    _addComment,
    _callNative
  } = helpers;
  _addComment('Draw HERO Header')
  _callNative('loadHeroData')
  _displayText()
  _overlayWait(true, [".UI_WAIT_TEXT"])

  _callNative('loadHeroMenu')
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