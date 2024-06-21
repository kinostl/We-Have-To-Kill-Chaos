const id = "FF_EVENT_DEFINE_ACTIONS";
const groups = ["Game Specific"];
const name = "Define Actions";

const l10n = (x)=>`${x}`
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

const compile = (input, helpers) => {
  const { caseVariableValue } = helpers;
  const falsePath = input["trueGetNextAction"];
  const action_cases = {}
  for(const rada of radarada){
    action_cases[rada[0]] = input[rada[1]]
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
