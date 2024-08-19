const id = "FS_FULL_MENU_COPY_SELECTION";
const groups = ["Full Screen Menu"];
const name = "Copy Menu Selection";

const fields = [
        {
            key: "setvar",
            type: "variable",
            label: "Copy Selection To Variable",
            defaultValue: "LAST_VARIABLE"
        }
    ]

const compile = (input, helpers) => {
    const {
        _setVariableMemInt8
    } = helpers;
    _setVariableMemInt8(input.setvar, "menu_selection");
};

module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
};