const id = "FF_EVENT_ENEMY_ROLL_INITIATIVE";
const groups = ["Game Specific"];
const name = "Enemies Rolls Initiatives";

const fields = [
    {
        type: "label",
        label: "Rolls the Enemies' initiatives"
    }
];

const compile = (input, helpers) => {
    const { _callNative } = helpers;
    _callNative("enemyRollInitiative");
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
