const id = "FF_EVENT_START_HERO_TURN";
const groups = ["Game Specific"];
const name = "Prepare for Hero Turn";

const fields = (
  [
    {
      type: "label",
      label: "Prepares data and graphics for Player's turn"
    }
  ]
);


const compile = (input, helpers) => {
  const {
    _displayText,
    _overlayWait,
    _addComment,
    _callNative
  } = helpers;
  _addComment('Prepare Hero Turn')
  _callNative('prepareHeroTurn')
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};