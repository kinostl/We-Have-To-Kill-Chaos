const id = "FF_EVENT_APPLY_TO_MULTIPLE";
const groups = ["Game Specific"];
const name = "Loop Over Multiple Variables";
const description =  "Applies a script to each variable. Destructive, modifies the selected Variable In Script as well. At the end of the script, Value in Script will be assigned to Value."

const subFields = []

for (let i = 0; i < 16; i++) {
  subFields.push({
    key: `__collapseCase${i}`,
    label: `Variable In Script #${i+1}`,
    conditions: [
      {
        key: "choices",
        gt: i,
      },
    ],
    type: "collapsable",
    defaultValue: true,
  })
  subFields.push({
    key: `value${i}`,
    label: `Variable In Script`,
    conditions: [
      {
        key: "choices",
        gt: i,
      },
      {
        key: `__collapseCase${i}`,
        ne: true,
      }
    ],
    type: "variable",
    defaultValue: "LAST_VARIABLE"
  })
  subFields.push({
    label: `Variable To Assign To Variable In Script...`,
    conditions: [
      {
        key: "choices",
        gt: i,
      },
      {
        key: `__collapseCase${i}`,
        ne: true,
      }
    ]
  })
  for (let j = 0; j < 16; j++) {
    subFields.push(
      {
        key: `value${i}_variable${j}`,
        label: `...On Loop #${j+1}`,
        conditions: [
          {
            key: "choices",
            gt: i,
          },
          {
            key: "array_size",
            gt: j,
          },
          {
            key: `__collapseCase${i}`,
            ne: true,
          }
        ],
        type: "variable",
        defaultValue: "LAST_VARIABLE"
      }
    )
  }
}

const fields = (
  [
    {
      key: "choices",
      label: "Number of Variables In Script",
      type: "number",
      min: 1,
      max: 16,
      defaultValue: 2,
    }, {
      key: "array_size",
      label: "Variables Per Loop",
      type: "number",
      min: 1,
      max: 16,
      defaultValue: 2,
    },
    ...subFields,
    {
      key: `__collapseEvents`,
      label: `Script Events`,
      type: "collapsable",
      defaultValue: false,
    },
    {
      key: "events",
      type: "events",
      conditions: [
        {
          key: `__collapseEvents`,
          ne: true,
        }
      ],
    }
  ]
);

const compile = (input, helpers) => {
  const {
    _addComment,
    _addNL,
    _setVariableToVariable,
    compileEvents
  } = helpers;
  _addComment(`Loop Over Multiple Values`);
  for (let i = 0; i < input["array_size"]; i++) {
    _addComment(`Iteration #${i+1}`)
    for (let j = 0; j < input["choices"]; j++) {
      _setVariableToVariable(input[`value${j}`], input[`value${j}_variable${i}`])
    }
    compileEvents(input["events"])
    for (let j = 0; j < input["choices"]; j++) {
      _setVariableToVariable(input[`value${j}_variable${i}`], input[`value${j}`])
    }
    _addNL();
  }
  _addComment(`End Loop Over Multiple Values`)
  _addNL();
};

module.exports = {
  id,
  name,
  description,
  groups,
  fields,
  compile,
};