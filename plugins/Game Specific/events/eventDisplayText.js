const id = "FF_EVENT_DISPLAY_TEXT";
const groups = ["Game Specific"];
const name = "Display Text Buffer";


const fields = (
  [
        {
            type: "number",
            label: "Height",
            description: "The height of the text, without the frame.",
            key: "h",
            min: 2,
            defaultValue: 2,
        },
  ]
);


const compile = (input, helpers) => {
    const textBoxHeight = input.h + 2;
    const textBoxY = 18 - textBoxHeight;
    helpers._overlayClear(0, 0, 20, textBoxHeight, ".UI_COLOR_WHITE", true);
    helpers._overlayMoveTo(0, textBoxY, ".OVERLAY_IN_SPEED");
    helpers._displayText();
    helpers._overlayWait(true, [
        ".UI_WAIT_WINDOW",
        ".UI_WAIT_TEXT",
        ".UI_WAIT_BTN_A",
    ]);
    helpers._overlayMoveTo(0, 18, ".OVERLAY_OUT_SPEED");
    helpers._overlayWait(true, [".UI_WAIT_WINDOW", ".UI_WAIT_TEXT"]);
    helpers._addNL();
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};