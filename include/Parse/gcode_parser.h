#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H

#include <stdint.h>

// ---  Gcode ---
typedef struct {
    int  gCode;
    int  mCode;
    float x;
    float y;
    float z;
    float i;
    float j;
    float feed;
} GcodeBlock;

extern GcodeBlock gcodeBlock;
extern volatile uint8_t blockReady;


void parseToken(char *tokenCode);
void executeBlock(void);
void processGcodeLine(char *gcodeText);

#endif