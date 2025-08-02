#include <string.h>
#include <stdlib.h>
#include "gcode_parser.h"
#include "mcode_actions.h"



static char *linePtr;
static char wordBuf[20];
static int wordIndex = 0;

GcodeBlock gcodeBlock;
volatile uint8_t blockReady = 0;

void parseToken(char *tokenCode) {
    char code = tokenCode[0];  
    float value = strtof(&tokenCode[1], NULL);  

    switch(code) {  
        case 'G': gcodeBlock.gCode = (int)value; break;  
        case 'M': gcodeBlock.mCode = (int)value; break;  
        case 'X': gcodeBlock.x = value; break;  
        case 'Y': gcodeBlock.y = value; break;  
        case 'Z': gcodeBlock.z = value; break;  
        case 'I': gcodeBlock.i = value; break;  
        case 'J': gcodeBlock.j = value; break;  
        case 'F': gcodeBlock.feed = value; break;  
    }        
}

void executeBlock(void){  
    if(blockReady){  
        switch(gcodeBlock.gCode) {  
            case 0: moveto(gcodeBlock.x, gcodeBlock.y, 0); break;  
            case 1: movetp(gcodeBlock.x, gcodeBlock.y, gcodeBlock.feed); break;  
            case 2: DrawArc(gcodeBlock.x, gcodeBlock.y, gcodeBlock.i, gcodeBlock.j, 1, gcodeBlock.feed); break;  
            case 3: DrawArc(gcodeBlock.x, gcodeBlock.y, gcodeBlock.i, gcodeBlock.j, 0, gcodeBlock.feed); break;  
        }  

         switch(gcodeBlock.mCode) {
            case 3: spindleOnCW(); break;    // M3
            case 4: spindleOnCCW(); break;   // M4
            case 5: spindleOff(); break;     // M5
            case 7: coolant1On(); break;     // M7
            case 8: coolant2On(); break;     // M8
            case 9: coolantAllOff(); break;  // M9
            case 2:                         // M2
            case 30: programEnd(); break;    // M30
            
        blockReady = 0;
    }
}

// ---  G-code ---
void processGcodeLine(char *gcodeText) {
    linePtr = gcodeText;
    wordIndex = 0;

    while (*linePtr) {
        if (*linePtr == ' ' || *linePtr == '\n') {
            wordBuf[wordIndex] = '\0'; 
            if (wordIndex > 0) {
                parseToken(wordBuf);
                wordIndex = 0;
            }
        if (*linePtr == '\n') {  
                blockReady = 1;       
                executeBlock();       
                memset(&gcodeBlock, 0, sizeof(gcodeBlock)); 
            }
        } else {  
            wordBuf[wordIndex++] = *linePtr;
        }  
        linePtr++;  
    }
}
