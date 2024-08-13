const id = "FF_EVENT_MY_MENU";
const groups = ["Game Specific"];
const name = "My Menu";
const l10n = require("../helpers/l10n").default;

const autoLabel = (fetchArg) => {
    const numItems = parseInt(fetchArg("items"));
    const text = Array(numItems)
        .fill()
        .map((_, i) => {
            return `"${fetchArg(`option${i + 1}`)}"`;
        })
        .join();
    return l10n("EVENT_MENU_LABEL", {
        variable: fetchArg("setvar"),
        text,
    });
};

const fields = [].concat(
    [
        {
            key: "actor",
            label: l10n("FIELD_ACTOR"),
            type: "actor",
            defaultValue: "$self$",
        },
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
            max: 8,
            defaultValue: 2,
        },
        {
            type: "break",
        },
    ],
    Array(8)
        .fill()
        .reduce((arr, _, i) => {
            const value = i + 1;
            arr.push(
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
            );
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
    {
        key: "layout",
        type: "select",
        label: l10n("FIELD_LAYOUT"),
        description: l10n("FIELD_LAYOUT_MENU_DESC"),
        options: [
            ["dialogue", l10n("FIELD_LAYOUT_DIALOGUE")],
            ["menu", l10n("FIELD_LAYOUT_MENU")],
        ],
        defaultValue: "dialogue",
    }
);


const wrap8Bit = (val) => (256 + (val % 256)) % 256;

const decOct = (dec) => wrap8Bit(dec).toString(8).padStart(3, "0");

const compile = (input, helpers) => {
    const {
        _overlayClear,
        _overlayMoveTo,
        _loadStructuredText,
        _displayText,
        _overlayWait,
        _addCmd,
        _callNative,
        _stackPushConst,
        _stackPop,
        getActorIndex,
        actorHide,
        scene,
        sprites,
        _stackPushReference,
        getVariableAlias
    } = helpers;

    const actor = scene.actors[getActorIndex(input.actor) - 1]
    const a_sprite = sprites.find((s) => s.id === actor.spriteSheetId)
    const a_width = a_sprite.boundsWidth

    if (input.actor == "player") {
        throw "Do not use the player actor as a menu cursor"
    }

    actorHide(input.actor)

    const options = [
        input.option1,
        input.option2,
        input.option3,
        input.option4,
        input.option5,
        input.option6,
        input.option7,
        input.option8,
    ].splice(0, input.items)

    if(input.cancelOnLastOption){
        _stackPushConst(1)
    }else{
        _stackPushConst(0)
    }

    if(input.cancelOnB){
        _stackPushConst(1)
    }else{
        _stackPushConst(0)
    }
    _stackPushConst(a_width / 8)
    _stackPushConst(input.items)
    _stackPushConst(getActorIndex(input.actor))
    _stackPushReference(getVariableAlias(input.setvar))

    const text = options.map((i, idx) => `\\003\\${decOct((a_width / 8) + 2)}\\${decOct(2 + idx)}${i}`).join('\r')

    _addCmd("VM_SET_CONST_UINT8 _show_actors_on_overlay, 1")

    // draw menu
    _overlayClear(0, 0, 20, input.items + 2, ".UI_COLOR_WHITE", true);
    _overlayMoveTo(0, 18 - input.items - 2, ".OVERLAY_IN_SPEED");

    _loadStructuredText(text)
    _displayText()
    _overlayWait(true, [".UI_WAIT_WINDOW", ".UI_WAIT_TEXT"]);

    // handle menuing
    _callNative("eventMyMenu")
    _overlayMoveTo(0, 18, ".OVERLAY_IN_SPEED");
    _overlayWait(true, [".UI_WAIT_WINDOW", ".UI_WAIT_TEXT"]);
    _stackPop(6)

    _addCmd("VM_SET_CONST_UINT8 _show_actors_on_overlay, 0")

};

module.exports = {
    id,
    name,
    autoLabel,
    groups,
    fields,
    compile,
    waitUntilAfterInitFade: true,
};