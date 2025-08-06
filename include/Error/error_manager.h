#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "stm32f103.h"
#include "motion.h"
#include <stdint.h>
#include <stdbool.h>

/* --- تنظیمات عمومی --- */
#define MAX_WORD_LEN     100 
#define MAX_FEEDRATE     2000
#define PARAM_MAX        260 
#define PARAM_MIN        75

/* --- انواع خطا --- */
typedef enum {
    ERR_NONE = 0,
    ERR_UNSUPPORTED_MCODE,
    ERR_UNSUPPORTED_GCODE,
    ERR_INVALID_FEEDRATE,
    ERR_OUT_OF_BOUND,
    ERR_EMERGENCY_STOP,
    ERR_NULL_POINTER,
    ERR_BUFFER_OVERFLOW
} CNC_ErrorStates;

/* --- متغیرهای خارجی --- */
extern CNC_ErrorStates currentError;

extern uint16_t feedrate;
extern volatile uint16_t step_index;
extern volatile uint16_t word_index;
extern char wordBuf[MAX_WORD_LEN];
extern uint8_t motion_state;

/* --- پروتوتایپ توابع --- */
void Pause_Timers(void);
void Disable_Driver(void);
bool userPressedResetButton(void);
void ResetBuffer(void);
void ClearError(void);
void ErrorHandler(CNC_ErrorStates err);

#endif /* ERROR_HANDLER_H */
