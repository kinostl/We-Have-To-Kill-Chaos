#ifndef FF_DEBUG
#define FF_DEBUG

#include <types.h>

#define VERBOSE FALSE
#define DEBUG FALSE

#if DEBUG == FALSE
#define EMU_BREAKPOINT (void)0;
#else
#include <gb/emu_debug.h>
#include <gb/crash_handler.h>
#endif


#if VERBOSE == FALSE
#define LOG(msg) (void)0;
#else
#include <gb/emu_debug.h>
#define LOG(msg) EMU_MESSAGE(msg)
#endif
#endif