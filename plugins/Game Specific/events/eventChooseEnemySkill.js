const id = "FF_EVENT_CHOOSE_SKILL";
const groups = ["Game Specific"];
const name = "Enemy Chooses Skill";

const fields = [
    {
        type: "label",
        label: "Chooses the Enemy's Skill and sets  it to Skill ID"
    }
];

const compile = (input, helpers) => {
    const { _callNative } = helpers;
    _callNative("chooseEnemySkill");
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
