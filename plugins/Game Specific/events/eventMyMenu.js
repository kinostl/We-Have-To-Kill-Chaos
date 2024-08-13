const id = "FF_EVENT_MY_MENU";
const groups = ["Game Specific"];
const name = "My Menu";


const fields = (
    [
        {
            key: "actor",
            type: "actor",
            label: "Cursor Actor",
            defaultValue: "LAST_ACTOR"
        },
        {
            key: "setvar",
            label: "Set Variable",
            type: "variable",
            defaultValue: "LAST_VARIABLE"
        },
        {
            key: "items",
            label: "Number of options",
            type: "number",
            defaultValue: 0,
            min: 0,
            max: 8
        },
        ...Array(MAX_STACK_SIZE)
            .fill()
            .map((x, i) => {
                return {
                    key: `option${i + 1}`,
                    label: `Set to ${i + 1} if`,
                    type: "textarea",
                    multiple: false,
                    defaultValue: "",
                    placeholder: `Item ${i+1}`,
                    conditions: [
                        {
                            key: "items",
                            gte: i + 1,
                        }
                    ],
                }
            })
    ]
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
        sprites
    } = helpers;

    const actor = scene.actors[getActorIndex(input.actor) - 1]
    const a_sprite = sprites.find((s) => s.id === actor.spriteSheetId)
    const a_width = a_sprite.boundsWidth

    if(input.actor == "player") {
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

    _stackPushConst(a_width / 8)
    _stackPushConst(input.items)
    _stackPushConst(getActorIndex(input.actor))
    _stackPushConst(input.setvar)

    const text = options.map((i, idx) => `\\003\\${decOct((a_width / 8) + 1)}\\${decOct(2 + idx)}${i}`).join('\r')

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
    _stackPop(4)

    _addCmd("VM_SET_CONST_UINT8 _show_actors_on_overlay, 0")

};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
    waitUntilAfterInitFade: true,
};