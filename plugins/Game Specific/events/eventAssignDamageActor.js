const l10n = require("../helpers/l10n").default;
const id = "FF_EVENT_SET_ACTOR_TO_DAMAGE";
const groups = ["Game Specific"];

const name = "Attach Actor to Damage";

const fields = [
    {
        key: "actorId_1",
        label: `${l10n("ACTOR")} 1`,
        type: "actor",
        defaultValue: "$self$",
    },
    {
        key: "actorId_2",
        label: `${l10n("ACTOR")} 2`,
        type: "actor",
        defaultValue: "$self$",
    },
    {
        key: "actorId_3",
        label: `${l10n("ACTOR")} 3`,
        type: "actor",
        defaultValue: "$self$",
    },
]

const compile = (input, helpers) => {
    const {getActorIndex, _stackPushConst, _stackPop, _callNative} = helpers;
    for(let i=3;i>0;i--){
        const actorIndex = getActorIndex(input[`actorId_${i}`]);
        _stackPushConst(actorIndex);
    }
    _callNative("assign_damage_actors");
    _stackPop(3);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
    allowedBeforeInitFade: true,
};