const id = "FF_EVENT_DEFINE_ACTIONS";
const groups = ["Game Specific"];
const name = "Define Actions";

const actions = [
    "ANIMATE/Explosions",
    "ATTACKER/Fight",
    "ANIMATE/Flash Enemy",
    "Player/Limit Break",
    "PICK/Item",
    "PICK/Magic",
    "Player/Block",
    "PICK/Run",
    "ATTACKER/Take Next Turn",
    "DEFENDER/Take Damage",
    "PICK/Enable Player",
    "PICK/Choice Made",
    "PANEL/Display Menu",
    "SCENE/Fade In",
    "ATTACKER/Start Next Turn",
    "PANEL/Close Panel",
    "TURN/Build Initiative",
    "REPORT/Prepare",
    "REPORT/Attack Results",
    "TURN/Roll Initiative",
    "REPORT/Reject Menu Choice",
    "PICK/Handle Choice",
    "TURN/Sort Initiative",
    "PANEL/Display Party",
    "PANEL/Open Panel",
    "PANEL/Display Current Actor",
    "PANEL/Display Party Actors",
    "PANEL/Hide Current Actor",
    "PANEL/Hide Party Actors"
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
                label: `${x} (${i})`,
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

function generateChartFromEvent(start, event, conn) {
    const start_id = start.replace(/[^a-zA-Z ]/g, "")
    if (!Array.isArray(event)) {
        if (!event.command) return null
        if (![
            "FF_EVENT_DISPATCH_ACTION",
            "EVENT_IF",
            "EVENT_SWITCH",
            "EVENT_SET_INPUT_SCRIPT",
            "EVENT_GROUP",
            "FF_EVENT_DEFINE_SKILLS"
        ].includes(event.command)) {
            if (event.children) throw `Unhandled Event with Children: ${event.command}`
            return null
        }
    }

    if (Array.isArray(event)) {
        if (event.length == 0) return null
        let x = start;
        let connector = conn

        for (let i = 0; i < event.length; i++) {
            const new_val = generateChartFromEvent(x, event[i], connector)
            if (new_val) {
                x = new_val
                connector = `-.->`
            }
        }
        if(x == start) return null
        return x
    }

    if (event.command === "FF_EVENT_DISPATCH_ACTION") {
        return `${start}${conn}${event.args.action}[${actions[event.args.action]}]`
    }

    if (event.command == "EVENT_IF") {
        const true_p = generateChartFromEvent(start, event.children.true, `--true-->`)
        const false_p = generateChartFromEvent(start, event.children.false, `--false-->`)

        return [
            true_p,
            false_p,
        ].filter((x) => x != null).join('\n')
    }

    if (event.command == "EVENT_SWITCH" || event.command == "FF_EVENT_DEFINE_SKILLS") {
        const output =  Object.values(event.children).map((x, i) => generateChartFromEvent(start, x, `-- ${i} -->`)).filter((x) => x != null)
        return output.join("\n")
    }

    if (event.command == "EVENT_SET_INPUT_SCRIPT") {
        return generateChartFromEvent(start, event.children.true, '-->')
    }

    if (event.command == "EVENT_GROUP") {
        let output = generateChartFromEvent(start, event.children, '-->')
        return output
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
        flows_for_chart.push(generateChartFromEvent(`${rada[0]}[${actions[rada[0]]}]`, input[rada[1]],'-->'))
    }

    flows_for_chart = flows_for_chart.join('\n').split('\n')
    // flows_for_chart = flows_for_chart.map((x)=>{
    //     if(x.startsWith('-->')){
    //         return x.substring(3)
    //     }
    //     if(x.startsWith('-.->')){
    //         return x.substring(4)
    //     }
    //     return x
    // })
    // flows_for_chart = flows_for_chart.filter((x, i, arr) => {
    //     let longest = true
    //     arr.forEach((y) => {
    //         if (x.includes(y) || y.includes(x)) {
    //             if (x !== y && longest) {
    //                 longest = x.length > y.length
    //             }
    //         }
    //     })
    //     return longest
    // })
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
