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

const fields = enemyData.map((x, i) => (
        {
          key: `enemyChance${i}`,
          label: `${x} % Chance`,
          type: "number",
          defaultValue: 0
        }
))


const compile = (input, helpers) => {
  const {
    _stackPushConst,
    _stackPop,
    _callNative
  } = helpers;
  // const totalChance = Array(6).reduce((x,_,i)=>x + input[`enemyChance${i}`],0)
  // if(totalChance != 100){
  //   throw "Total Chance must be 100"
  // }

  for (let i = 0; i < 6; i++) {
    const enemyType = input[`enemyType${i}`]
    const enemyChance = input[`enemyChance${i}`]
    _stackPushConst(enemyType)
    _stackPushConst(enemyChance)
    _stackPushConst(i)
    //_callNative("handleEnemySlots")
    _stackPop(3)
  }
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};
