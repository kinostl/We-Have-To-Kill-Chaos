const id = "FO_EVENT_CONNECT_MAPS";
const groups = ["Plugins"];
const name = "Connect Maps";

const fields = (
  []
);


const compile = (input, helpers) => {
    const coord_scenes = helpers
        .scenes
        .filter((scene) => scene.script
            .some((script) => script.command == "FO_EVENT_SET_MAP_COORDS")
        )

    // throw JSON.stringify(coord_scenes.map((scene)=>scene.symbol))
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};