const id = "FF_EVENT_MAKE_MAX_GLOBAL_VARS_H";
const groups = ["Plugins"];
const name = "Make Max Global Vars Header";
const description = "Creates 'data/max_global_vars.h'."
const fields = [{
    label: description
}];

const compile = (input, helpers) => {
    const {
        writeAsset,
        variableAliasLookup
    } = helpers;

    let __output = "#ifndef _MAX_GLOBAL_VARS_H_INCLUDE\n"
    __output+="#define _MAX_GLOBAL_VARS_H_INCLUDE\n"
    __output+=`#include "vm.h"\n`
    __output+=`#define MAX_GLOBAL_VARS ${Object.values(variableAliasLookup).length}\n`
    __output+="#endif"

    writeAsset("max_global_vars.h", __output)
};


module.exports = {
    id,
    name,
    groups,
    fields,
    compile,
    description,
    waitUntilAfterInitFade: true
};

