#include <string.h>
#pragma bank 255
#include "my_crash_handler.h"
#include "load_font_into_bg.h"


void MyHandleCrash(const char * message) BANKED{
    loadFontIntoBkg();
    UBYTE x=0;
    UBYTE y=0;
    for(UBYTE i=0;i<strlen(message);i++){
        write_bg_char(x, y, message[i]);
        x++;
        if(x>=20){
            x=0;
            y++;
        }
    }
}