const id = "FS_FULL_MENU_WRITE_COMPLEX_SHOP_MENU";
const groups = ["Full Screen Menu"];
const name = "FS Shop Menu";
const l10n = require("../helpers/l10n").default;

const shop_fields = [].concat(
    [
        {
            key: "setvar",
            label: l10n("FIELD_SET_VARIABLE"),
            description: l10n("FIELD_VARIABLE_DESC"),
            type: "variable",
            defaultValue: "LAST_VARIABLE",
        },
        {
            key: "items",
            label: l10n("FIELD_NUMBER_OF_OPTIONS"),
            description: l10n("FIELD_NUMBER_OF_OPTIONS_DESC"),
            type: "number",
            min: 2,
            max: 18,
            defaultValue: 2,
        },
        {
            type: "break",
        },
    ],
    Array(18)
        .fill()
        .reduce((arr, _, i) => {
            const value = i + 1;
            const options = [
                {
                    key: `option${i + 1}`,
                    label: l10n("FIELD_SET_TO_VALUE_IF", { value: String(i + 1) }),
                    description: l10n("FIELD_SET_TO_VALUE_IF_MENU_DESC", {
                        value: String(i + 1),
                    }),
                    hideFromDocs: i >= 2,
                    type: "textarea",
                    singleLine: true,
                    defaultValue: "",
                    placeholder: l10n("FIELD_ITEM", { value: String(i + 1) }),
                    conditions: [
                        {
                            key: "items",
                            gt: value,
                        },
                    ],
                },
                {
                    key: `option${i + 1}`,
                    label: l10n("FIELD_SET_TO_VALUE_IF", { value: String(i + 1) }),
                    description: l10n("FIELD_SET_TO_VALUE_IF_MENU_DESC", {
                        value: String(i + 1),
                    }),
                    hideFromDocs: i >= 2,
                    type: "textarea",
                    singleLine: true,
                    defaultValue: "",
                    placeholder: l10n("FIELD_ITEM", { value: String(i + 1) }),
                    conditions: [
                        {
                            key: "items",
                            eq: value,
                        },
                        {
                            key: "cancelOnLastOption",
                            ne: true,
                        },
                    ],
                },
                {
                    key: `option${i + 1}`,
                    label: l10n("FIELD_SET_TO_VALUE_IF", { value: "0" }),
                    description: l10n("FIELD_SET_TO_VALUE_IF_MENU_DESC", { value: "0" }),
                    hideFromDocs: true,
                    type: "textarea",
                    singleLine: true,
                    defaultValue: "",
                    placeholder: l10n("FIELD_ITEM", { value: String(i + 1) }),
                    conditions: [
                        {
                            key: "items",
                            eq: value,
                        },
                        {
                            key: "cancelOnLastOption",
                            eq: true,
                        },
                    ],
                }

            ].map((x) => {
                return {
                    type: "group",
                    fields: [
                        x,
                        {
                            type: "number",
                            label: l10n("FIELD_VALUE"),
                            key: `option${i + 1}_cost`,
                            defaultValue: 0,
                            conditions: [
                                ...x.conditions,
                                {
                                    key: "isShop",
                                    eq: true
                                }
                            ]
                        }
                    ],
                    conditions: x.conditions
                }
            })
            options[2] = options[2].fields[0]
            arr.push(...options)
            return arr;
        }, []),
    {
        type: "break",
    },
    {
        type: "checkbox",
        label: l10n("FIELD_LAST_OPTION_CANCELS"),
        description: l10n("FIELD_LAST_OPTION_CANCELS_DESC"),
        key: "cancelOnLastOption",
    },
    {
        type: "checkbox",
        label: l10n("FIELD_CANCEL_IF_B"),
        description: l10n("FIELD_CANCEL_IF_B_DESC"),
        key: "cancelOnB",
        defaultValue: true,
    },
);

const fields = (
    [
        {
            key: "isShop",
            label: "This is a Shop",
            description: "Is This a Shop?",
            type: "checkbox",
            defaultValue: false,
        },
        ...shop_fields,
        {
            type: "group", key: "args", fields: [
                {
                    key: "x",
                    type: "value",
                    label: "Start X",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    },
                },
                {
                    key: "y",
                    type: "value",
                    label: "Start Y",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    },
                }, {
                    key: "dx",
                    type: "value",
                    label: "End X",
                    defaultType: "number",
                    defaultValue: {
                        "number": 0,
                        "variable": "LAST_VARIABLE"
                    },
                }, {
                    key: "dy",
                    type: "value",
                    label: "End Y",
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