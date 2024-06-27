const id = "FF_EVENT_SORT_TURN_QUEUE";
const groups = ["Game Specific"];
const name = "Sort Turn Order Queue";

const collator = new Intl.Collator()

const fields = (
  [
    {
      key: "destination",
      type: "label",
      label: "Sorts the Turn Queue"
    }
  ]
);

const compile = (input, helpers) => {
  const {
    _callNative,
    _addComment,
    _addNL,
  } = helpers;
  _addComment(`Sort Turn Slots`);
  _callNative("handleSortTurnOrder")
  _addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};