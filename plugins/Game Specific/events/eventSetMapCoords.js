const id = "FO_EVENT_SET_MAP_COORDS";
const groups = ["Plugins"];
const name = "Set Map Coords";

const fields = (
  [{key:"x", type:"number", defaultValue: 0},{key:"y", type:"number", defaultValue: 0}]
);


const compile = (input, helpers) => {
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};