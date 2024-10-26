https://guides.gamercorner.net/ff/random-encounters/

Looks like enemies use a "Family" system to determine their AI. With the ability to be in multiple families. This should be replicated somehow.

160 x 144 would allow for 3 x 3 enemies and nothing else with the current 6x6 tile enemies that are currently implemented. I think reducing the enemy count will be fine given that this system might be a bit more tactical than the original version.

Battle Design - Inspired by FFX + Digimon RPGs + Four Heros Of Light. Actions have a Speed cost(?) that changes where you are in the initiative. The initiative is an ongoing list, like in FFX and Digimon.

Can have 6 enemies on screen with a array of 4x5 tile boxes

enemy turn, move the screen left, and move the control box left, and make it look like the enemy team is taking a turn in the same fashion as the player side?

Enough space for maybe 6 Commands. Commands need to be 4 letters at most, with a cost at the end of 1,2,3,4

Last command is probably something like Skip that gives you another stock and goes to the next initiative

Command ideas

MONK gets "Focus", which provides more stocks than the normal Skip command.
MONK can pool together attacks, letting them spend multiple Stock on a single attack, letting them bypass the initiative system a little bit

Actually just stealing these sounds great lol.

https://finalfantasy.fandom.com/wiki/Black_Mage_(The_4_Heroes_of_Light)
https://finalfantasy.fandom.com/wiki/Bandit_(The_4_Heroes_of_Light) (Thief mechs)
https://finalfantasy.fandom.com/wiki/White_Mage_(The_4_Heroes_of_Light)
https://finalfantasy.fandom.com/wiki/Fighter_(The_4_Heroes_of_Light)
https://finalfantasy.fandom.com/wiki/Hero_(The_4_Heroes_of_Light) (Monk Option 1)
https://finalfantasy.fandom.com/wiki/Dancer_(The_4_Heroes_of_Light) (Monk Option 2)
https://finalfantasy.fandom.com/wiki/Spell_Fencer_(The_4_Heroes_of_Light) (Replace Red Mage with this?)

4HOL has an emnity system and no enemy selection. Should that be implemented?

bkg does need to be on screen to copy from, for some reason. There might be a way to wait for it?

Can't use bkg submapping for moving the middle bar left and right, so might just be best to not have the screen move. Its posible to submap multiple times when the camera stops moving so maybe that could be considered.

Either that or just consider only submapping the enemies and do all the backgrounding manually.

Using the overlay like a drawer worked really well. I think I can probably put the initiative guide to the right of the menu and have the Select button expose it or something. I can probably add an Advanced View to the screen too.

"Extra" column in an advanced view would have 2 tiles per row if I replicate the card stacking thing. Maybe 3 if I go for an extending style.

Opponent selection, have overlay move out of the way. Use the right bar as a list. Have pointer point at list and battlefield. Maybe put hp or something in utility bar.

I can put a bunch of menu things into a seperate bg and use this to copy them as needed.

```asm
OP_VM_OVERLAY_SET_MAP   = 0x56
;-- Copies a tilemap starting at a given tile ID (`IDX`) to the overlay at a position.
; @param IDX Tile ID where tilemap starts.
; @param X_IDX X position on the overlay.
; @param Y_IDX Y position on the overlay.
; @param BANK Bank number of tilemap.
; @param BKG Tilemap.
.macro VM_OVERLAY_SET_MAP IDX, X_IDX, Y_IDX, BANK, BKG
        .db OP_VM_OVERLAY_SET_MAP, #>BKG, #<BKG, #<BANK, #>Y_IDX, #<Y_IDX, #>X_IDX, #<X_IDX, #>IDX, #<IDX
.endm
```

Tile ID might be too weird to try to deal with, unless I just want to reimplement dialogue (again) which might not be the worst idea. Or look into using Advanced Dialogue Ver B - I think thats already optimized to do something like that. I think VM_OVERLAY_SET_MAP was made for copying Fonts over into the Dialog

I think I just want to get the FF Font and then use https://www.gbstudio.dev/docs/scripting/gbvm/gbvm-operations/#vm_load_text intelligently, specifically with :

\003\x\y Sets the position for the next character
\004\x\y Sets the position for the next character relative to the last character

consider using font to draw frames dynamically.

Can probably have plugin manage it

```
<======>
|      |
|      |
|      |
[______]
```

Maybe something like this. I don't think these symbols are used by the FF Font.

Or I could just do engine hacks lol. https://github.com/chrismaltby/gb-studio/blob/f2a1031f3e495cd779da3a32e42162f7f2b3f307/appData/src/gb/src/core/ui.c#L141

```c
void ui_draw_frame(UBYTE x, UBYTE y, UBYTE width, UBYTE height) BANKED {
    if (height == 0) return;
#ifdef CGB
    if (_is_CGB) {
        VBK_REG = 1;
        fill_win_rect(x, y, width, height, overlay_priority | (text_palette & 0x07u));
        VBK_REG = 0;
    }
#endif
    UBYTE * base_addr = GetWinAddr() + (y << 5) + x;
    ui_draw_frame_row(base_addr, ui_frame_tl_tiles, width);
    if (--height == 0) return;
    if (height > 1)
        for (UBYTE i = height - 1; i != 0; i--) {
            base_addr += 32;
            ui_draw_frame_row(base_addr, ui_frame_l_tiles, width);
        }
    base_addr += 32;
    ui_draw_frame_row(base_addr, ui_frame_bl_tiles, width);
}
```

okay turns out VM_OVERLAY_CLEAR does this already

B-Side does all of this already lol

Text buffer still shafts itself pretty quickly, so might just want to do my own thing anyway - I might be wrong, I just keep forgetting how text and boxes work. 

Yup, it does hit a buffer at some point. I might not need that much text though. Still, makes a lot of things a lot easier.

I can copy from another bg using vmemcpy and 

    tileset_bank = *(uint8_t *) VM_REF_TO_PTR(FN_ARG0);
    tileset = *(tileset_t **) VM_REF_TO_PTR(FN_ARG1);
    
and

    {
      key: "backgroundId",
      label: "Tilemap",
      description: "The tilemap is the background image with the tiles you want to swap in.",
      type: "background",
      defaultValue: "", 
      flexBasis: "100%",
    },
    
and


    _setConst(".ARG0", `___bank_${bgSymbol}_tileset`)
    _setConst(".ARG1", `_${bgSymbol}_tileset`)
    
    
https://discord.com/channels/554713715442712616/575070105919029295/1241117758721101917 


```c
#pragma bank 255

#include <gbdk/platform.h>

#include "data_manager.h"
#include "vm.h"
#include "bankdata.h"
#include "system.h"

extern UBYTE image_bank;
extern UBYTE image_attr_bank;
extern unsigned char *image_ptr;
extern unsigned char *image_attr_ptr;

void handle_bkg_submap(UINT8 x, UINT8 y, UINT8 w, UINT8 h, INT16 offset_x, INT16 offset_y) NONBANKED;

void background_submap(SCRIPT_CTX * THIS) OLDCALL BANKED {
    int16_t src_x = *(int16_t*)VM_REF_TO_PTR(FN_ARG0);
    int16_t src_y = *(int16_t*)VM_REF_TO_PTR(FN_ARG1);
    int16_t dest_x = *(int16_t*)VM_REF_TO_PTR(FN_ARG2);
    int16_t dest_y = *(int16_t*)VM_REF_TO_PTR(FN_ARG3);
    int16_t w = *(int16_t*)VM_REF_TO_PTR(FN_ARG4);
    int16_t h = *(int16_t*)VM_REF_TO_PTR(FN_ARG5);

    int16_t offset_x = src_x - dest_x;
    int16_t offset_y = src_y - dest_y;

    handle_bkg_submap(dest_x, dest_y, w, h, offset_x, offset_y);
}

void handle_bkg_submap(UINT8 x, UINT8 y, UINT8 w, UINT8 h, INT16 offset_x, INT16 offset_y) NONBANKED {
    UINT8 _save = CURRENT_BANK;

#ifdef CGB
    if (_is_CGB) { 
        SWITCH_ROM(image_attr_bank);
        VBK_REG = 1;
        set_bkg_submap(x, y, w, h, image_attr_ptr + offset_x + (offset_y * image_tile_width), image_tile_width);
        VBK_REG = 0;
    }
#endif

    SWITCH_ROM(image_bank);
    set_bkg_submap(x, y, w, h, image_ptr + offset_x + (offset_y * image_tile_width), image_tile_width);
    
    SWITCH_ROM(_save);
}
```

Okay less stupid plan.

Step 1. Load tileset to overlay using VM_LOAD_TILES or VM_LOAD_TILESET
Step 2. Copy VRAM to background
Step 3. Done??

Yeah turns out LOAD_TILES replaces the whole tileset the same way REPLACE_TILE does. Theres no way to do this, just have everything you want inside the map you're already on instead.


Old method was fine, nice waste of three days. Learned a lot about how the tileset system works. Turns out its all hardware based and if you try to dynamically change it you're just gonna have a bad time.

So, new goal now that 256 x 256 process is confirmed to be perfectly fine. 

New Goal: Get an actual fight going on on screen

Start with making sure players and enemy (Imp) has HP

Make sure player characters have the basic Fight Command - Don't worry about Resource System yet.

Make sure enemy can choose targets and attack.

Hit chance of 60/20/15/5 ?

## Battle Menu

We can replicate that Display Menu does as a custom plugin.
Don't use VM_CHOICE since that uses the UI's smaller pointer and is limited.
Have it wait for the A button to be pressed, assuming player control is still available.

VM_OVERLAY_WAIT

VM_OVERLAY_WAIT IS_MODAL, WAIT_FLAGS

Wait for the UI operation(s) completion

    IS_MODAL: indicates whether the operation is modal: .UI_MODAL, or not: .UI_NONMODAL
    WAIT_FLAGS: bit field, set of events to be waited for:
    .UI_WAIT_NONE - No wait
    .UI_WAIT_WINDOW - Wait until the window moved to its final position
    .UI_WAIT_TEXT - Wait until all the text finished rendering
    .UI_WAIT_BTN_A - Wait until "A" is pressed
    .UI_WAIT_BTN_B - Wait until "B" is pressed
    .UI_WAIT_BTN_ANY - Wait until any button is pressed


    ; Text Menu
    VM_LOAD_TEXT            0
    .asciz "\001\001\003\003\002\002\001Fight\n\002\001Run"
    VM_OVERLAY_CLEAR        0, 0, 10, 4, .UI_COLOR_WHITE, ^/(.UI_AUTO_SCROLL | .UI_DRAW_FRAME)/
    VM_OVERLAY_MOVE_TO      10, 18, .OVERLAY_SPEED_INSTANT
    VM_OVERLAY_MOVE_TO      10, 14, .OVERLAY_IN_SPEED
    VM_DISPLAY_TEXT
    VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/
    VM_CHOICE               VAR_S1_ACTION_CHOICE, .UI_MENU_CANCEL_B, 2
        .MENUITEM           1, 1, 1, 2, 0, 2
        .MENUITEM           1, 2, 1, 2, 1, 0
    VM_OVERLAY_MOVE_TO      10, 18, .OVERLAY_OUT_SPEED
    VM_OVERLAY_WAIT         .UI_MODAL, ^/(.UI_WAIT_WINDOW | .UI_WAIT_TEXT)/
    VM_OVERLAY_MOVE_TO      0, 18, .OVERLAY_SPEED_INSTANT

    Party starts with 500G on NES

# Idea For Short Menu

```
NAMESP
AAX000
AAY111
```

NAMESP is the Name Space
AA
AA is the character's walking sprite
X is the HP *Symbol*
Y is the AP *Symbol*
000 is the HP Amount
111 is the AP Amount? Maybe symbols.
or do first 1 as AP and other 2 as status symbols

```
AANAME
AAX000
AAY111
```

Could also do this and get full sized sprites, which would allow for animations. Then shrink names down to 4 and use the two extra spaces in the big view for Status Effects. I like that and combining it with the 1SS thing above.

## Small Mode

```
AANAME
AAX000
AAY1SS
```

SS is Status Effect Area

```
NAMESS
 AA000
 AAYYY
 AAYYY
```

YYY is the AP Blocks

VM_SET_FONT 1

VM_PUSH_CONST 0
VM_PUSH_CONST .FRAME_TILE_ID

VM_REPLACE_TILE .ARG0, ___bank_tileset_frame_0, _tileset_frame_0, .ARG1, .FRAME_LENGTH
VM_POP 2

  // Enemies don't have Agility, only Evade
  // Should Players join the queue via Ability or Evade?
  /**
   * 4. The formula for a character's Evasion is:

    Evasion = 48 + AGL - Armor Weight

   */
  // Players should queue via Evade as well.

  // I think 1dHP + EVA sounds fun
  // Reroll each turn to allow for things like HASTE to matter more

# Fighter Weapons

Swords have High Hit% Mid Damage
Axes have Mid Hit% High Damage

Maybe have Swords return a + to replicate this?

# Spell Books

Maybe it could be fun to have a Dicey Dungeons kind of thing for these?

# Fixing Grinding

If we should, maybe add side quests? Theres enough side npcs for it.

# Magic

Casters can maybe put more orbs into a spell to change it between 1/2/etc

# Enemy Basics

An enemy may have up to 8 Spells and up to 4 Skills (From the FAQ)

## Original Encounter Numbers

Most pattern tables contain 2 small enemies, and 2 large enemies. These are 
capable of three formation types:

(Up to) 9 Small Enemies
(Up to) 4 Large Enemies
(Up to) 2 Large Enemies and 6 Small Enemies

Two pattern tables contain 2 fiends each, and one pattern table is devoted 
entirely to Chaos. Each of these can only display one enemy sprite at a time.

We only have 10 x 12 squares so that means...

(a) 6 Small Enemies
(b) 2 Large Enemies
(c) 1 Large Enemy & 2 Small Enemies

Small = 4 * 5
Large = 6 * 6

## Determining what to put on the battlefield

Step 1. Determine number of large enemies. If 2, draw them and end this list.
Step 2a. Only 1 large enemy was rolled. Roll number of Small enemies between 0 and 2.
Step 2b. No large enemies were rolled. Roll number of Small enemies between 1 and 6.
Step 3. Draw enemies 

### Step 3a. Small + Large

Draw small enemies on top row. Then draw large enemy under them. This lets us standardize for Only Small. After drawing small set y offset to small y endpoint.
Draw large enemy at small y endpoint.

### Step 3b. Only Small

Loop through the rolled enemies, drawing row by row. Should make Small + Large somewhat easy to use with this.
Draw first enemy at 1,6. Set x offset to ... no not great solution theres a way to just do this with a dual loop. 

### Step 3c. Only large

Draw the first large enemy then set the y offset to 7. Draw second enemy at y offset.


### Loop Solution

set y to 6
for 1..6 as i
    if i % 2:
        bkg_submap(1,y)
    else:
        bkg_submap(4,y)
        y+= enemy_height

# Indirection Tool Plugin

```
=List of Variables to Iterate Through=
*Number of Items*
[list of dropdowns ala switch]
*Type of Action?* (Loop, Map, etc.)
[Events applied to each thing]
```

```
Number of Vars
[
    Var To Use For Indirection,
    [List of Vars]
] * Number of Vars
---
[Events applied to indirect vars]
```

Indirection might be an option, so is just replacing them inside the plugin?
Error out if Indirect Groups aren't same size.

Overworld stuff and battle visuals satisfactory ... next is making the random encounters real and not just visual changes?

Is a plugin system my best option for manipulating their values? Its six slots, and thats a lot of similar things going on that I can't use scripts on nicely, and I want things to reset at the start of a battle.

```
Set Slots
1. Imp
2. Imp
3. Wolf
4. None
5. None
6. None
```

Maybe something like this, but that'd require doing things manually? 

```
Encounter Chances
1. Imp     75%
2. Wolf    20%
3. Horse    5%
4. None
5. None
6. None
```

This would allow the slots to set themselves.

```
Load Enemy Slot
Slot [1/2/3/4/5/6]
```

Fill in the Attacker or Enemy data into the easily usable parts. This is probably an Engine plugin.

```
HP: Hit Points          SATK: Status Attack     GOLD: Gold
ATK: Attack             ELEM: S. Attack Element EXP.: Experience
ACC: Accuracy (#Hits)*  TYPE: Enemy Family
CRT: Critical Rate      WEAK: Weakness(es)      FORM: Formations
DEF: Defense            RESI: Resistances       LCTN: Locations
EVA: Evasion
M.D: Magic Defense      MAGIC:   X/128 - SPELLS
MOR: Morale             SPECIAL: X/128 - SKILLS
```

Enemy data

Enemies have 18 datas?
Probably part of the engine plugin mentioned above.

# Bosses

## Primary Bosses

Garland
Pirates
Piscodemon
Astos
Vampire
Lich (Fiend of Earth)
Marilith (Fiend of Fire)
Kraken (Fiend of Water)
Tiamat, Fiend of Air
Chaos

## All Bosses

Garland
Pirates
Piscodemon
Astos
Vampire
Lich (Fiend of Earth)
Red Dragon (Not officially a boss)
Marilith (Fiend of Fire)
Evil Eye
Dragon Zombies (Optional)
Kraken (Fiend of Water)
Blue Dragon (Not officially a boss)
Warmech (Optional, Superboss)
Tiamat, Fiend of Air
Boss Rush
Chaos

10 Primary bosses, so 5 levels per boss. Which means demo goes up to Level 5.

Last left off: Trying to figure out how to make the Party screen look good during the opponent's turn. Maybe not displaying text during battle anymore and using numbers instead?

Use moogle from FF3 for EX Garland
https://www.spriters-resource.com/nes/finalfantasy3jpn/sheet/32907/

FF3 damage numbers just uses the standard font, in pink for some reason. Try yellow to match modern but if that doesn't work use pink as well.

Took 3 days to fix a problem that should have been an hour to fix, and the fix doesn't even look good. Programming is stupid. show/hide and stop/start effects the OAM or something. Had to do the de/activate trick at the time of animation. Causes minor slowdown. Sucks, don't like how it looks as code, ignoring all these facts before I make a whole ass Reorder Sprite Layers plugin that no one will understand. Fuck you OAM.

Started item stuff, thought I could do it in the short menu, might need to do it in an item scene or an overlay event.

Items should be a screen lightly inspired by GBA and Pokemon. Two columns of item names + symbols + count. Key/Item/Equip tabs on top(?) Description of the item at the bottom. Columns don't have boxes, description does. I like GBA's method of 

```
SNAME  XX
```

I like how that looks for items but maybe I should still do the full screen item screen, it looks like it might be confusing otherwise.

NES FF1 only used inventory for overworld items. Equip has its own screen just for weapons and another just for armor. There seems to be no in-battle equipment changing.

GBA version has a proper / more traditional / more modern equip screen that integrates everything.

I think removing in-battle equip is the more fun option and easier to design around.

Lets drop Item stuff for now and work on the equip screen.

Equip screen can probably take inspiration from GBA. Drop the idea of seperating armor and weapon screens and weapon inventory

Equip screen, stats show on the left side, and sub-stats on the right. During equip, replace stats with choices?

## Idea for moving more of the Combat scene into C

I don't really need all that much of whats in the scene to be handled by the GBS side of things, so I should probably start moving the dispatcher and etc stuff into C since it can probably do things a bit more managbly in that. Then that means I can have the actors in the scene *only* care about animation. This can be accomplished with the current method of having a set of transfer variables, to handle animation settings only.

### Reasoning

The current implementation is cumbersome and difficult to manage now that it has scaled up. Its elegant at the start, but the number of skills I want to introduce necessitates a more comprehensive solution to organization and my options there are to either fork GBS entirely and add whole new pages for data management or to start using C even more. The C Solution seems more entertaining to me, and it lets me make use of the built-in scene system, which makes menu style scenes a *lot* easier since I don't need to work around the built in collisions. 


### Explosions

Explosion animations already act similarly to what I'm imagining, so they can be used as a reference.

### Damage Numbers

I have no idea how these numbers are being changed. Is this happening in the C Code or in the Dispatcher?

### Characters

These can likely be easier to manage as well since I'd be able to make use of the scene initializer function instead of the initial script.
That might be overkill and ignore the seperation of concerns I'm looking for.

### Dispatcher

Removing this would be best, as cute as it is, its a hacked solution. Any logic in it should be in C. Any view logic should be getting handled by the actors displaying that. I shouldn't need a camera manager, so that shouldn't be a concern yet.

### Menu System

This part may or may not be tricky, I want to remove the current Trigger based solution as it won't be necessary with the Menu Scene based implementation I'm looking at now. Which should also hopefully allow for the flexibility in the menu'ing that it looks like I need. (Having the cursor move to different spots dynamically).

#### Menu Item

I probably need to look into a Menu Item structure to assist with this, and some functions to help with it. Something that can keep track of the line height and enforce the width of the characters. That kinda stuff. I can probably move the plugin that has the Abilities & Cost into C as well here.

### Background Stuff

This is mostly in the C code but I'll need to move more of it into the scene type instead of the area it currently is.

## Animation Mode and other Modes

By the looks of it, I'm gonna need to add an animation mode to make the new attempt at the dispatch action thingy work, so that it can handle waiting for animations to complete. I'll probably need some kinda glue var to handle locking. Yay mutexes.