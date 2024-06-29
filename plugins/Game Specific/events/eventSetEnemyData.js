const id = "FF_EVENT_SET_ENEMY_DATA";
const groups = ["Game Specific"];
const name = "Setup Enemy Data";

const enemyData = [
  "IMP",
  "GrIMP",
  "WOLF",
  "MADPONY"
]

const enemyOpts = enemyData.map((x, i) => [i, x])

const _getVarAlias = (var_name) => {
  return getVariableAlias(
    Object.values(variablesLookup)
      .find((x) => x.name == var_name).id
  )
}


// Maybe I want this to actually be the enemy sets?

const fields = [
  {
    type:"label",
    label:"Sets up and Draws the Enemy Encounter"
  }
]

const compile = (input, helpers) => {
  const {
    _callNative,
  } = helpers;
  _callNative("setupEnemySlots")
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};