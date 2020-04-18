// TIMER.C
// Copyright (C)1997 BJ Eirich
// Timer irq-hooking and PIT speed setting routines.

#include <stdio.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#include "engine.h" // for valloc()
#include "vc.h"

#define PIT0 0x40
#define PIT1 0x41
#define PIT2 0x42
#define PITMODE 0x43
#define PITCONST 1193180L

#define OCR1    0x20
#define IMR1    0x21

#define OCR2    0xA0
#define IMR2    0xA1

unsigned hooktimer = 0;
unsigned char an = 0, tickctr = 0, sec = 0, min = 0, hr = 0;

namespace {
    unsigned lastTick = 0;
}

void sethz(unsigned int hz) {
}

void restorehz() {
}

namespace {
    long globalTimer = 0;
    unsigned int timer_count = 0;
    int vc_timer;
}

void incTimerCount(void*);

int timer_init() {
    globalTimer = emscripten_set_interval(&incTimerCount, 10, nullptr);
    return 0;
}

int timer_close() {
    emscripten_clear_interval(globalTimer);
    globalTimer = 0;
    return 0;
}

void delay(int ms) {
}

int time() {
    return timer_count;
}

void setTimerCount(int offset) {
    timer_count = offset;
}

void incTimerCount(void*) {
    timer_count++;
    vc_timer++;
    lastTick++;

    tickctr++;
    if (tickctr == 100) {
        tickctr = 0;
        sec++;

        if (sec == 60) {
            sec = 0;
            min++;
            if (min == 60) {
                min = 0;
                hr++;
            }
        }
    }

    // FIXME: HookTimer.  Can't run it here.
}

// The original engine ran this in a DOS interrupt.
// We can't do that, so we instead play catch up.  We must call this function after each "asyncify"d call.
void runTimerHooks() {
    while (lastTick > 0) {
        --lastTick;
        if (an) {
            check_tileanimation();
        }
        if (hooktimer) {
            ExecuteHookedScript(hooktimer);
        }
    }
}

void decTimerCount() {
    timer_count--;
}

int getTimerCount() {
    return timer_count;
}

int getVcTimer() {
    return vc_timer;
}

void setVcTimer(int value) {
    vc_timer = value;
}
