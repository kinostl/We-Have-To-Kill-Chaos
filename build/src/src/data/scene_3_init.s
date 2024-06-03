.module scene_3_init

.include "vm.i"
.include "data/game_globals.i"
.include "macro.i"

.globl b_wait_frames, _wait_frames, _fade_frames_per_step, _camera_settings, ___bank_scene_1, _scene_1

.area _CODE_255

.LOCAL_TMP0_CAMERA_MOVE_ARGS = -4
.LOCAL_TMP1_WAIT_ARGS = -4
.LOCAL_TMP2_IF_VALUE = -4
.LOCAL_TMP3_IF_VALUE = -4
.LOCAL_ACTOR = -4
.LOCAL_TMP5_IF_VALUE = -5
.LOCAL_TMP6_LOCAL = -5
.LOCAL_TMP7_IF_VALUE = -6

___bank_scene_3_init = 255
.globl ___bank_scene_3_init

_scene_3_init::
        VM_LOCK

        VM_RESERVE              6

        ; Variable Set To
        VM_SET_CONST            VAR_ENEMY_1_HP, 0

        ; Camera Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1280
            .R_REF_SET  .LOCAL_TMP0_CAMERA_MOVE_ARGS
            .R_INT16    1152
            .R_REF_SET  ^/(.LOCAL_TMP0_CAMERA_MOVE_ARGS + 1)/
            .R_STOP
        ; -- Move Camera
        VM_CAMERA_SET_POS       .LOCAL_TMP0_CAMERA_MOVE_ARGS

        ; Overlay Move To
        VM_OVERLAY_MOVE_TO      20, 0, 0
        VM_OVERLAY_WAIT         .UI_MODAL, .UI_WAIT_WINDOW

        ; Wait N Frames
        VM_SET_CONST            .LOCAL_TMP1_WAIT_ARGS, 1
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP1_WAIT_ARGS

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 3
        VM_FADE_IN              1

        VM_PUSH_CONST           1
        VM_PUSH_CONST           1
        VM_PUSH_CONST           10
        VM_PUSH_CONST           4
        VM_PUSH_CONST           0
        VM_PUSH_CONST           18
        VM_CALL_NATIVE          b_copyBkgToBkg, _copyBkgToBkg
        VM_POP                  6
        VM_PUSH_CONST           1
        VM_PUSH_CONST           5
        VM_PUSH_CONST           5
        VM_PUSH_CONST           4
        VM_PUSH_CONST           0
        VM_PUSH_CONST           26
        VM_CALL_NATIVE          b_copyBkgToBkg, _copyBkgToBkg
        VM_POP                  6
        VM_PUSH_CONST           1
        VM_PUSH_CONST           5
        VM_PUSH_CONST           5
        VM_PUSH_CONST           4
        VM_PUSH_CONST           20
        VM_PUSH_CONST           0
        VM_CALL_NATIVE          b_copyBkgAttrToBkgAttr, _copyBkgAttrToBkgAttr
        VM_POP                  6
        VM_OVERLAY_SET_SUBMAP 0, 0, 8, 18, 24, 14

        VM_OVERLAY_SET_SUBMAP 1, 1, 6, 4, 8, 18

        VM_PUSH_CONST           1
        VM_PUSH_CONST           1
        VM_CALL_NATIVE          b_handleSetEnemyData, _handleSetEnemyData
        VM_POP                  2
        ; Variable Set To
        VM_SET_CONST            VAR_S1_LOCAL_0, 0

        ; Variable Set To
        VM_SET_CONST            VAR_S1_ENEMY_TURN, 0

        ; Variable Set To
        VM_SET_CONST            VAR_S1_ENEMY_SLOT, 0

        ; Variable Set To
        VM_SET_CONST            VAR_S1_ENEMY_HP, 1

        ; Variable Set To
        VM_SET_CONST            VAR_PLAYER_1_HP, 99

        ; Variable Set To
        VM_SET_CONST            VAR_S1_ENEMY_TYPE, 0

        ; Call Script: Change Enemy Slot
        VM_PUSH_CONST           VAR_S1_ENEMY_HP ; Variable V1
        VM_PUSH_VALUE           VAR_S1_ENEMY_SLOT
        VM_CALL_FAR             ___bank_script_2, _script_2

        START_NEXT_TURN=.

        ; If
        ; -- Calculate value
        VM_RPN
            .R_REF      VAR_S1_ENEMY_TURN
            .R_INT16    1
            .R_OPERATOR .EQ
            .R_REF_SET  .LOCAL_TMP2_IF_VALUE
            .R_STOP
        ; If
        VM_IF_CONST             .NE, .LOCAL_TMP2_IF_VALUE, 0, 1$, 0
        VM_JUMP PLAYER_TURN

        VM_JUMP                 2$
1$:
        VM_JUMP ENEMY_TURN

2$:

        ENEMY_TURN=.

        ; Overlay Move To
        VM_OVERLAY_MOVE_TO      20, 0, 0
        VM_OVERLAY_WAIT         .UI_MODAL, .UI_WAIT_WINDOW

        ; If
        ; -- Calculate value
        VM_RPN
            .R_INT16    50
            .R_OPERATOR .RND
            .R_INT16    2
            .R_OPERATOR .MOD
            .R_REF_SET  .LOCAL_TMP3_IF_VALUE
            .R_STOP
        ; If
        VM_IF_CONST             .NE, .LOCAL_TMP3_IF_VALUE, 0, 3$, 0
        VM_JUMP                 4$
3$:
        ; Variable Decrement By 1
        VM_RPN
            .R_REF      VAR_PLAYER_1_HP
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  VAR_PLAYER_1_HP
            .R_STOP

4$:

        ; Variable Set To
        VM_SET_CONST            VAR_S1_ENEMY_TURN, 0

        VM_JUMP END_THIS_TURN

        PLAYER_TURN=.

        ; Overlay Move To
        VM_OVERLAY_MOVE_TO      12, 0, 0
        VM_OVERLAY_WAIT         .UI_MODAL, .UI_WAIT_WINDOW

        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1536
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    1152
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

        ; If
        ; -- Calculate value
        VM_RPN
            .R_INT16    50
            .R_OPERATOR .RND
            .R_INT16    2
            .R_OPERATOR .MOD
            .R_REF_SET  .LOCAL_TMP5_IF_VALUE
            .R_STOP
        ; If
        VM_IF_CONST             .NE, .LOCAL_TMP5_IF_VALUE, 0, 5$, 0
        VM_JUMP                 6$
5$:
        ; Variable Decrement By 1
        VM_RPN
            .R_REF      VAR_S1_ENEMY_HP
            .R_INT8     1
            .R_OPERATOR .SUB
            .R_REF_SET  VAR_S1_ENEMY_HP
            .R_STOP

6$:

        ; Variable Set To
        VM_SET_CONST            VAR_S1_ENEMY_TURN, 1

        ; Wait For Input
        VM_INPUT_WAIT           48

        VM_JUMP END_THIS_TURN

        END_THIS_TURN=.

        ; -- Evaluate expression VAR_PLAYER_1_HP<=0||VAR_S1_ENEMY_HP<=0
        VM_RPN
            .R_REF      VAR_PLAYER_1_HP
            .R_INT16    0
            .R_OPERATOR .LTE
            .R_REF      VAR_S1_ENEMY_HP
            .R_INT16    0
            .R_OPERATOR .LTE
            .R_OPERATOR .OR
            .R_REF_SET  .LOCAL_TMP6_LOCAL
            .R_STOP
        ; If
        ; -- Calculate value
        VM_RPN
            .R_REF      .LOCAL_TMP6_LOCAL
            .R_REF_SET  .LOCAL_TMP7_IF_VALUE
            .R_STOP
        ; If
        VM_IF_CONST             .NE, .LOCAL_TMP7_IF_VALUE, 0, 7$, 0
        VM_JUMP START_NEXT_TURN

        VM_JUMP                 8$
7$:
        ; Load Scene
        VM_SET_CONST_INT8       _fade_frames_per_step, 3
        VM_FADE_OUT             1
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    8320
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    11904
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR
        VM_ACTOR_SET_DIR        .LOCAL_ACTOR, .DIR_DOWN
        VM_SET_CONST_INT8       _camera_settings, .CAMERA_LOCK
        VM_RAISE                EXCEPTION_CHANGE_SCENE, 3
            IMPORT_FAR_PTR_DATA _scene_1

8$:

        ; Stop Script
        VM_STOP
