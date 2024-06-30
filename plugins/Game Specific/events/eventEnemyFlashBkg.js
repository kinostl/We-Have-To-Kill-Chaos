const id = "FF_EVENT_ENEMY_FLASH_BKG";
const groups = ["Game Specific"];
const name = "Enemy Flashes BKG";

const fields = [
    {
        type: "label",
        label: "Makes the Current Enemy flash their space"
    }
];

const compile = (input, helpers) => {
    const { _callNative } = helpers;
    _callNative("enemyFlashBKG");
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
