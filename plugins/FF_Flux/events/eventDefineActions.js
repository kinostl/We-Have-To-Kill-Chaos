const id = "FF_EVENT_DEFINE_ACTIONS";
const groups = ["Game Specific"];
const name = "Define Actions";

const l10n = (x) => `${x}`
const actions = [
    "ANIMATE/Explosions",
    "ATTACKER/Fight",
    "Player/Shield",
    "Player/Limit Break",
    "PICK/Item",
    "PICK/Magic",
    "Player/Block",
    "PICK/Run",
    "ATTACKER/Take Next Turn",
    "DEFENDER/Take Damage",
    "PICK/Enable Player",
    "PICK/Choice Made",
    "MENU/Open Panel",
    "SCENE/Fade In",
    "ATTACKER/Start Next Turn",
    "MENU/Close Panel",
    "TURN/Build Initiative",
    "REPORT/Prepare",
    "REPORT/Attack Results",
    "TURN/Roll Initiative",
    "REPORT/Reject Menu Choice",
    "PICK/Handle Choice",
    "TURN/Sort Initiative"
];

const collator = new Intl.Collator()
const radarada = []

const fields = [
    {
        key: "variable",
        type: "variable",
        defaultValue: "LAST_VARIABLE",
    },
    actions.map((x, i) => {
        radarada.push([i, `true${i}`])
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
    {

        key: `__collapseCaseGetNextAction`,
        label: `Else`,
        type: "collapsable",
        defaultValue: true,
    },
    {
        key: `trueGetNextAction`,
        conditions: [
            {
                key: `__collapseCaseGetNextAction`,
                ne: true,
            },
        ],
        type: "events",

    }
].flat(2);

let ifCount = 0;

const generateChartFromEvent = (start, event) => {
    if (Array.isArray(event)) {
        return event.map((subev)=>generateChartFromEvent(start, subev)).filter((x)=>x).join('-->')
    }
    if(event.command === "FF_EVENT_DISPATCH_ACTION"){
        return `${start}-->${event.args.action}[${actions[event.args.action]}]`
    }
    // if(event.command === "EVENT_IF"){
    //     ifCount++;
    //     const if_start = `if_count_${ifCount}{${ifCount}}`
    //     const true_side = generateChartFromEvent(`${if_start}--true`,event.children.true)
    //     const false_side = generateChartFromEvent(`${if_start}--false`, event.children.false)
    //     const branch = [`${start}-->${if_start}`]
    //     if(true_side !== `${if_start}--true->`){
    //         branch.push(true_side)
    //     }
    //     if(false_side !== `${if_start}--false->`){
    //         branch.push(false_side)
    //     }
    //     return branch.join('\n')
    // }
    if(event.command == "EVENT_IF"){
        return [
            generateChartFromEvent(start, event.children.true),
            generateChartFromEvent(start, event.children.false),
        ].join('\n')
    }
    if(event.command == "EVENT_SWITCH"){
        return Object.values(event.children).map((x)=>generateChartFromEvent(start,x)).join('\n')
    }
    if (event.command == "EVENT_SET_INPUT_SCRIPT") {
        return generateChartFromEvent(start, event.children.true)
    }
    if([
        "EVENT_GROUP",
    ].includes(event.command)){
        return generateChartFromEvent(start, event.children)
    }
    if(event.children){
        throw `Unhandled Event with Children: ${event.command}`
    }
}

const compile = (input, helpers) => {
    const { caseVariableValue, additionalOutput } = helpers;

    //   if (!additionalOutput['dat_chart']) {
    //     additionalOutput['dat_chart'] = {
    //       filename: 'dat_chart.md',
    //       data: `a${input["action"]}(${actions[input["action"]]})-.->${entity.id}[(${entity.name})]\n`
    //     }
    //   } else {
    //     additionalOutput['dat_chart'].data = `a${input["action"]}(${actions[input["action"]]})-.->${entity.id}[(${entity.name})]\n` + additionalOutput['dat_chart'].data
    //   }
    const falsePath = input["trueGetNextAction"];
    let flows_for_chart = []
    const action_cases = {}

    for (const rada of radarada) {
        action_cases[rada[0]] = input[rada[1]]
    }

    for (const rada of radarada) {
        flows_for_chart.push(generateChartFromEvent(`${rada[0]}[${actions[rada[0]]}]`, input[rada[1]]))
    }

    flows_for_chart = flows_for_chart.join('\n').split('\n')
    flows_for_chart = flows_for_chart.map((x)=>{
        if(x.startsWith('-->')){
            return x.substring(3)
        }
        return x
    })
    flows_for_chart = flows_for_chart.filter((x, i, arr) => {
        let longest = true
        arr.forEach((y) => {
            if (x.includes(y) || y.includes(x)) {
                if (x !== y && longest) {
                    longest = x.length > y.length
                }
            }
        })
        return longest
    })
    flows_for_chart = [...new Set(flows_for_chart)]
    additionalOutput["dat_chart"] = {
        filename: "dat_chart.md",
        data: [
            '```mermaid',
            'flowchart TD',
            ...flows_for_chart,
            '```'
        ].join('\n')
    }

    caseVariableValue(input.variable, action_cases, falsePath);
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};
