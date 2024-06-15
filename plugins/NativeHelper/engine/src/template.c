#pragma bank 255

#include "vm.h"
#include <gb/gb.h>
#include "data_manager.h"
//Standard boilerplate


//Change myFunctionName, its what you'll be putting into NativeHelper'
void myFunctionName(SCRIPT_CTX * THIS) OLDCALL BANKED { //Boilerplate that the compiler wants
    uint16_t stackVar0 =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0)); //Lets you view the variable on the stack, Goes up to FN_ARG8
    //Pointers are currently not supported by NativeHelper due to automatic popping.
}