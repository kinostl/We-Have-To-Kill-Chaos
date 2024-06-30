const id = "FF_EVENT_CHECK_ENEMY_ALIVE";
const groups = ["Game Specific"];
const name = "Check Enemy Is Alive";

const fields = [
    {
        type: "label",
        label: "Checks if the Current Enemy is Alive"
    }
];

const compile = (input, helpers) => {
    const { _callNative } = helpers;
    _callNative("checkEnemyAlive");
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
