
const id = "FF_EVENT_INIT_ENEMY";
const groups = ["Game Specific"];
const name = "Initialize Enemy";

const fields = (
  [
    {
      key: "enemySlot",
      label: "Enemy Slot",
      type: "select",
      width: "50%",
      defaultValue: 1,
      options: [
        [1, "First Slot"],
        [2, "Second Slot"],
        [3, "Third Slot"],
        [4, "Fourth Slot"],
        [5, "Fifth Slot"],
        [6, "Sixth Slot"]
      ]
    },
    {
      key: "enemyType",
      label: "Enemy Type",
      type: "select",
      width: "50%",
      defaultValue: 1,
      options: [
        [1, "Imp"]
      ]
    },
  ]
);

const compile = (input, helpers) => {
  const {
    _callNative,
    _stackPushConst,
    _stackPop,
  } = helpers;

  _stackPushConst(input.enemySlot);
  _stackPushConst(input.enemyType);

  _callNative('handleSetEnemyData');

  _stackPop(2);
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};