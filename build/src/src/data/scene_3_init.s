.module scene_3_init

.include "vm.i"
.include "data/game_globals.i"

.globl b_wait_frames, _wait_frames, _fade_frames_per_step

.area _CODE_255

.LOCAL_ACTOR = -4
.LOCAL_TMP2_WAIT_ARGS = -4
.LOCAL_TMP1_CAMERA_MOVE_ARGS = -6

___bank_scene_3_init = 255
.globl ___bank_scene_3_init

_scene_3_init::
        VM_LOCK

        VM_RESERVE              6

        ; Actor Set Active
        VM_SET_CONST            .LOCAL_ACTOR, 0

        ; Actor Set Animation Tick
        VM_ACTOR_SET_ANIM_TICK  .LOCAL_ACTOR, 3

        ; Actor Hide
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_HIDDEN     .LOCAL_ACTOR, 1

        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_PUSH_CONST           32
        VM_PUSH_CONST           32
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_OVERLAY_SET_SUBMAP_EX .ARG5

        VM_POP                  6
        ; Camera Move To
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1280
            .R_REF_SET  .LOCAL_TMP1_CAMERA_MOVE_ARGS
            .R_INT16    1152
            .R_REF_SET  ^/(.LOCAL_TMP1_CAMERA_MOVE_ARGS + 1)/
            .R_STOP
        ; -- Move Camera
        VM_CAMERA_SET_POS       .LOCAL_TMP1_CAMERA_MOVE_ARGS

        ; Overlay Show
        VM_OVERLAY_SHOW         20, 0, 0, 0

        VM_PUSH_CONST           1
        VM_PUSH_CONST           1
        VM_PUSH_CONST           10
        VM_PUSH_CONST           4
        VM_PUSH_CONST           0
        VM_PUSH_CONST           18
        VM_CALL_NATIVE          b_copyWinToBkg, _copyWinToBkg
        VM_POP                  6
        VM_PUSH_CONST           1
        VM_PUSH_CONST           5
        VM_PUSH_CONST           5
        VM_PUSH_CONST           4
        VM_PUSH_CONST           0
        VM_PUSH_CONST           26
        VM_CALL_NATIVE          b_copyWinToBkg, _copyWinToBkg
        VM_POP                  6
        VM_PUSH_CONST           0
        VM_PUSH_CONST           0
        VM_PUSH_CONST           8
        VM_PUSH_CONST           18
        VM_PUSH_CONST           24
        VM_PUSH_CONST           7
        VM_OVERLAY_SET_SUBMAP_EX .ARG5

        VM_POP                  6
        VM_PUSH_CONST           1
        VM_PUSH_CONST           1
        VM_PUSH_CONST           6
        VM_PUSH_CONST           4
        VM_PUSH_CONST           8
        VM_PUSH_CONST           18
        VM_OVERLAY_SET_SUBMAP_EX .ARG5

        VM_POP                  6
        VM_PUSH_CONST           1
        VM_PUSH_CONST           1
        VM_CALL_NATIVE          b_handleSetEnemyData, _handleSetEnemyData
        VM_POP                  2
        ; Variable Set To
        VM_SET_CONST            VAR_ACTION, 1

        ; Actor Set Position
        ; -- Calculate coordinate values
        VM_RPN
            .R_INT16    1152
            .R_REF_SET  ^/(.LOCAL_ACTOR + 1)/
            .R_INT16    256
            .R_REF_SET  ^/(.LOCAL_ACTOR + 2)/
            .R_STOP
        ; -- Position Actor
        VM_SET_CONST            .LOCAL_ACTOR, 0
        VM_ACTOR_SET_POS        .LOCAL_ACTOR

        ; Wait N Frames
        VM_SET_CONST            .LOCAL_TMP2_WAIT_ARGS, 1
        VM_INVOKE               b_wait_frames, _wait_frames, 0, .LOCAL_TMP2_WAIT_ARGS

        ; Fade In
        VM_SET_CONST_INT8       _fade_frames_per_step, 3
        VM_FADE_IN              1

        ; Stop Script
        VM_STOP
