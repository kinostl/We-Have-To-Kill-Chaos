const textDialogue = (inputText, avatarId, helper) => {
    const input = Array.isArray(inputText) ? inputText : [inputText];

    const initialNumLines = input.map(helper.textNumLines);
    const maxNumLines = Math.max(2, Math.max.apply(null, initialNumLines));
    const textBoxHeight = Math.min(maxNumLines, 5) + 2;
    const textBoxY = 18 - textBoxHeight;

    helper._addComment("Text Dialogue (Battle Version)");
    input.forEach((text, textIndex) => {
        let avatarIndex = undefined;
        if (avatarId) {
            const { avatars } = helper.options;
            avatarIndex = avatars.findIndex((a) => a.id === avatarId);
            if (avatarIndex < 0) {
                avatarIndex = undefined;
            }
        }

        helper._loadStructuredText(text, avatarIndex, 5);
        helper._overlayClear(0, 0, 20, textBoxHeight, ".UI_COLOR_WHITE", true);
        if (textIndex === 0) {
            helper._overlayMoveTo(0, textBoxY, ".OVERLAY_IN_SPEED");
        }
        helper._displayText();
        helper._overlayWait(true, [
            ".UI_WAIT_WINDOW",
            ".UI_WAIT_TEXT",
            ".UI_WAIT_BTN_A",
        ]);
        // if (textIndex === input.length - 1) {
        //     helper._overlayMoveTo(0, 18, ".OVERLAY_OUT_SPEED");
        //     helper._overlayWait(true, [".UI_WAIT_WINDOW", ".UI_WAIT_TEXT"]);
        // }
    });
    helper._addNL();
};

const l10n = require("../helpers/l10n").default;

const id = "FF_EVENT_BATTLE_TEXT";
const groups = ["EVENT_GROUP_DIALOGUE"];

const autoLabel = (fetchArg, args) => {
    if (([].concat(args.text) || []).join()) {
        return `Battle - ${l10n("EVENT_TEXT_LABEL", {
            text: fetchArg("text"),
        })}`;
    } else {
        `Battle - ${l10n("EVENT_TEXT")}`;
    }
};

const fields = [
    {
        key: "text",
        type: "textarea",
        placeholder: l10n("FIELD_TEXT_PLACEHOLDER"),
        multiple: false,
        defaultValue: "",
        flexBasis: "100%",
    },
    {
        key: "avatarId",
        type: "avatar",
        toggleLabel: l10n("FIELD_ADD_TEXT_AVATAR"),
        label: l10n("FIELD_TEXT_AVATAR"),
        description: l10n("FIELD_TEXT_AVATAR_DESC"),
        defaultValue: "",
        optional: true,
    },
];

const compile = (input, helpers) => {
    textDialogue(input.text || " ", input.avatarId, helpers);
};

module.exports = {
    id,
    description: l10n("EVENT_TEXT_DESC"),
    name: "Display Battle Text",
    autoLabel,
    groups,
    fields,
    compile,
    waitUntilAfterInitFade: true,
};
