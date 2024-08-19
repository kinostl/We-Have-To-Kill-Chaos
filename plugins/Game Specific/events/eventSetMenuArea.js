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
                defaultValue: "1",
                min: "1"
            }

        ]
    },
    {
        key: "load_val",
        type: "value",
        label: "Load Value as Selection",
        defaultType: "number",
        defaultValue: "1"
    }
]

const compile = (input, helpers) => {
    const {
        actorSetById,
        actorSetPosition,
        _setMemInt8ToVariable,
        _setConstMemInt8,
        _setConstMemInt16,
        variableSetToScriptValue,
        variableValueOperation,
        _declareLocal,
        _markLocalUse
    } = helpers;
    const valHolder = _declareLocal(`fs_menu_min_sel`, 1, true);
    variableSetToScriptValue(valHolder, input.load_val);
    variableValueOperation(valHolder, ".MAX", 1);

    actorSetById("player")
    actorSetPosition(input.x, input.y);
    _setConstMemInt16("cursor_base_pos", ((input.y * 16 * 8) >> 7) << 7);
    _setMemInt8ToVariable("menu_selection", valHolder);
    _setConstMemInt8("max_menu_selection", input.max);

    _markLocalUse(valHolder)
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};