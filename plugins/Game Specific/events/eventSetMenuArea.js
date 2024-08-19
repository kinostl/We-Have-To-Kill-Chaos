const id = "FS_FULL_MENU_SET_AREA";
const groups = ["Full Screen Menu"];
const name = "Set Menu Area";

const fields = [
    {
        type: "group", fields: [
            {
                key: "x",
                type: "number",
                label: "X",
                defaultValue: "0"
            }, {
                key: "y",
                type: "number",
                label: "Y",
                defaultValue: "0"
            }, {
                key: "max",
                type: "number",
                label: "Max",
                defaultValue: "0"
            }

        ]
    }
]

const compile = (input, helpers) => {
    const {
        actorSetById,
        actorSetPosition,
        _setConstMemInt8,
        _setConstMemInt16
    } = helpers;
    actorSetById("player")
    actorSetPosition(input.x, input.y);
    _setConstMemInt16("cursor_base_pos", ((input.y * 16 * 8) >> 7) << 7);
    _setConstMemInt8("menu_selection", 1);
    _setConstMemInt8("max_menu_selection", input.max);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};