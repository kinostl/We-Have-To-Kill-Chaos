
const id = "FF_EVENT_SET_MENU";
const groups = ["Game Specific"];
const name = "Update Menu";

const fields = (
  [
    {
      key: "menuSlot0",
      type: "text",
      defaultValue: "",
    },
    {
      key: "menuSlot1",
      type: "text",
      defaultValue: "",
    },
    {
      key: "menuSlot2",
      type: "text",
      defaultValue: "",
    },
    {
      key: "menuSlot3",
      type: "text",
      defaultValue: "",
    },
    {
      key: "menuSlot4",
      type: "text",
      defaultValue: "",
    },
    {
      key: "menuSlot5",
      type: "text",
      defaultValue: "",
    },
  ]
);

const compile = (input, helpers) => {
  const {
    _loadText,
    _string,
    _displayText,
    _overlayWait
  } = helpers;

  const str = [
    "menuSlot0",
    "menuSlot1",
    "menuSlot2",
    "menuSlot3",
    "menuSlot4",
    "menuSlot5"
  ].map((i)=>input[i].slice(0, 6).padEnd(6)).join("\\n")
  _loadText(0)
  _string(`\\001\\1\\003\\2\\14${str}`)
  _displayText()
  _overlayWait(true, [".UI_WAIT_TEXT"])
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};