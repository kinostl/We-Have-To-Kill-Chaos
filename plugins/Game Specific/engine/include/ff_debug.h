#ifndef FF_DEBUG
#define FF_DEBUG

#include <types.h>
#include <gb/crash_handler.h>
#include <gb/emu_debug.h>

#define VERBOSE FALSE
#define DEBUG FALSE

#if !DEBUG
#define EMU_BREAKPOINT (void)0;
#endif


#if !!VERBOSE
#define LOG(msg) EMU_MESSAGE(msg)
#else
#define LOG(msg) (void)0;
#endif
#endif