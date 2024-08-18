const id = "FS_FULL_MENU_WRITE_BG_TEXT";
const groups = ["Full Screen Menu"];
const name = "Write BG Text";

const fields = (
    [
        {
            key: "bg_text",
            type: "textarea",
            defaultValue: "",
            placeholder: "Background Text"
        },
        {
            type: "group", key: "args", fields: [
                {
                    key: "x",
                    type: "value",
                    label: "X",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    },
                },
                {
                    key: "y",
                    type: "value",
                    label: "Y",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    },
                }, {
                    key: "w",
                    type: "value",
                    label: "W",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    },
                }, {
                    key: "h",
                    type: "value",
                    label: "H",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    }
                }
            ]
        }
    ]
);

const compile = (input, helpers) => {
    const {
        _loadStructuredText,
        _declareLocal,
        _stackPush,
        variableSetToScriptValue,
        _stackPop,
        _callNative,
        _displayText
    } = helpers;

    _loadStructuredText(input.bg_text);

    const valHolder = _declareLocal(`fs_menu_call_native_val`, 1, true);
    variableSetToScriptValue(valHolder, input.x);
    _stackPush(valHolder)
    variableSetToScriptValue(valHolder, input.y);
    _stackPush(valHolder)
    variableSetToScriptValue(valHolder, input.w);
    _stackPush(valHolder)
    variableSetToScriptValue(valHolder, input.h);
    _stackPush(valHolder)

    _callNative("writeTextToBg");
    _stackPop(4);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};