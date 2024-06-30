const id = "FF_EVENT_DEFINE_SKILLS";
const groups = ["Game Specific"];
const name = "Define Skills";

const actions = [
    "FIGHT", "GOBLIN_PUNCH", "HOWL", "THRASH"
].map((x)=>{
    return x.split("_")
        .map((y) => {
            const cap = y.substring(0, 1).toUpperCase()
            const rest = y.substring(1).toLowerCase()
            return `${cap}${rest}`
        }).join(" ");
});

const collator = new Intl.Collator()
const fields = [
    {
        key: "variable",
        type: "variable",
        defaultValue: "LAST_VARIABLE",
    },
    actions.map((x, i) => {
        return [
            {

                key: `__collapseCase${i}`,
                label: `${x}`,
                type: "collapsable",
                defaultValue: true,
            },
            {
                key: `true${i}`,
                conditions: [
                    {
                        key: `__collapseCase${i}`,
                        ne: true,
                    },
                ],
                type: "events",

            }
        ]
    }).sort((a, b) => collator.compare(a[0].label, b[0].label)),
].flat(2);

let ifCount = 0;


const compile = (input, helpers) => {
    const { caseVariableValue } = helpers;

    const action_cases = {}

    actions.forEach((_,i)=>{

        action_cases[i] = input[`true${i}`]
    })

    caseVariableValue(input.variable, action_cases, action_cases[0]);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
