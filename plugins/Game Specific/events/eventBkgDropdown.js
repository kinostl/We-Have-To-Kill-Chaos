const id = "FO_EVENT_BKGSELECT";
const groups = ["Plugins"];
const name = "BKG Select";

const fields = (
  [
    {
      key: "background",
      label: "BKG Select",
      type: "background",
    },
  ]
);

const compile = (input, helpers) => {
    const { backgrounds } = helpers;
    throw JSON.stringify({
      bkg: input["background"],
      backgrounds
    });
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
  };