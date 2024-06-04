
const id = "FF_EVENT_SET_HERO";
const groups = ["Game Specific"];
const name = "Update HERO";

const fields = (
  [
    {
      key: "name",
      type: "text",
      defaultValue: "",
      maxLength: 6
    },
    {
      key: "hp",
      type: "text",
      defaultValue: "",
      maxLength: 3
    },
    {
      key: "ap",
      type: "number",
      defaultValue: 0,
      maxLength: 6
    }
  ]
);

const compile = (input, helpers) => {
  const {
    _loadText,
    _string,
    _displayText,
    _overlayWait
  } = helpers;

  const _name = input["name"].padEnd(6, " ")
  const _hp = input["hp"].padStart(6, " ")

  _loadText(0)
  _string(`\\001\\1\\003\\2\\2${_name}\\r${_hp}\\r   +++\\r   +++`)
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