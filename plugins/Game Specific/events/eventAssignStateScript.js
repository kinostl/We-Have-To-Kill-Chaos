const id = "FF_EVENT_SET_SCRIPT_TO_STATE";
const groups = ["Game Specific"];
const stateNames = [
    "Animate Player Attacking",
    "Animate Enemy Attacking",
    "Animate Enemy Damaged",
    "Animate Party Win",
    "Animate Party Lose"
]
const name = "Attach Script to Animation State";
const autoLabel = (fetchArg) => {
    const state = Number(fetchArg("state"));
    return `Attach Script to "${stateNames[state]}"`;
};

const fields = [
    {
        key: "state",
        label: "Select Scene State",
        type: "select",
        defaultValue: "0",
        options: stateNames.map((x,i)=>[i,x]),
    },
    {
        key: "__scriptTabs",
        type: "tabs",
        defaultValue: "scriptinput",
        values: {
          scriptinput: "On State",
        },
    },
    {
        key: "script",
        label: "State Script",
        description: "State Script",
        type: "events",
        allowedContexts: ["global", "entity"],
        conditions: [
          {
            key: "__scriptTabs",
            in: [undefined, "scriptinput"],
          },
        ],
      },
  ];
  
const compile = (input, helpers) => {
    const { appendRaw, _compileSubScript, _addComment, additionalOutput, writeAsset, getNextLabel } = helpers;
    input.script.unshift({"command":"EVENT_SCRIPT_LOCK","args":{},"id":`rpg_animation_lock_${getNextLabel()}`});
    input.script.push({"command":"EVENT_SCRIPT_UNLOCK","args":{},"id":`rpg_animation_unlock_${getNextLabel()}`});
    const ScriptRef = _compileSubScript("state", input.script, "test_symbol" + input.state);
    const stateNumber = `${input.state}`;
    const bank = `___bank_${ScriptRef}`;
    const ptr = `_${ScriptRef}`

    _addComment("Set Platformer Script");
    appendRaw(`VM_PUSH_CONST ${stateNumber}`);
    appendRaw(`VM_PUSH_CONST ${bank}`);
    appendRaw(`VM_PUSH_CONST ${ptr}`);
    appendRaw(`VM_CALL_NATIVE b_assign_state_script, _assign_state_script`);
    appendRaw(`VM_POP 3`);

    const header_name = "rpg_combat_animation_states.h";
    if (!additionalOutput[header_name]) {
        writeAsset(
            header_name,
      /*h*/`
#ifndef RPG_COMBAT_ANIMATION_STATES
#define RPG_COMBAT_ANIMATION_STATES
typedef enum {
  ${stateNames.map((x) => x.replaceAll(/\s/g, "_").toUpperCase()).join(',\r  ')}
} RPG_ANIMATION_STATE;
#define RPG_ANIMATION_STATE_LENGTH ${stateNames.length}
#endif
`.trim()
        )

    }

};
  
  module.exports = {
    id,
    name,
    autoLabel,
    groups,
    fields,
    compile,
    allowedBeforeInitFade: true,
  };
  
  