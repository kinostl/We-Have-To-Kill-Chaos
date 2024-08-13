const id = "DEBUG_HELP_EVENT_VIEW_EVENTS";
const groups = ["Debug Tools"];
const name = "View Event As Comment";

const fields = (
  [
    {
      key: "action",
      type: "events"
    }
  ]
);

const compile = (input, helpers) => {
  const {
    _addComment,
    _addNL
  } = helpers;

  throw JSON.stringify(input["action"], null, 4)
  _addComment()
  _addNL()
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};