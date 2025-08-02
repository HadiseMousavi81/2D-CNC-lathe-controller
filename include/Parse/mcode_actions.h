#ifndef MCODE_ACTIONS_H
#define MCODE_ACTIONS_H

#include <stdint.h>

// ---  ---
void spindleOnCW(void);    // M3
void spindleOnCCW(void);   // M4
void spindleOff(void);     // M5

void coolant1On(void);     // M7
void coolant2On(void);     // M8
void coolantAllOff(void);  // M9

void programEnd(void);     // M2 / M30

#endif