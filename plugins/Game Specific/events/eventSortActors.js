const l10n = require("../helpers/l10n").default;

const id = "FF_SORT_ACTORS";
const groups = ["Game Specific"];
const name = "Sort Actors";

const fields = [
    { label: "The higher the priority, the lower it goes on the scene.", width: "100%" },
    { type: "break" },
    {
        key: "items",
        label: l10n("FIELD_NUMBER_OF_OPTIONS"),
        description: l10n("FIELD_NUMBER_OF_OPTIONS_DESC"),
        type: "number",
        min: 2,
        max: 20,
        defaultValue: 2,
    },
    {
        type: "break",
    },
    ...Array(20)
        .fill(0)
        .map((x, i) => [{
            key: `option${i + 1}`,
            hideFromDocs: i >= 2,
            label: `Actor Priority ${i + 1}`,
            type: "actor",
            defaultValue: "$SELF$",
            conditions: [
                {
                    key: "items",
                    gt: i,
                },
            ],
        }, {
            type: "break"
        }]).flat()
];

const compile = (input, helpers) => {
    const { actorDeactivate, actorActivate } = helpers;
    const actors = Object.entries(input).filter((([key])=>key.startsWith("option"))).map(([key, value])=>value).slice(0, input["items"])
    actors.forEach((actor) => actorDeactivate(actor));
    actors.forEach((actor) => actorActivate(actor));
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};