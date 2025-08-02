#include "mcode_actions.h"
#include "stm32f103.h"  


static void pinSet(GPIO_TypeDef *port, uint16_t pin) {
    port->BSRR = pin;
}

static void pinReset(GPIO_TypeDef *port, uint16_t pin) {
    port->BRR = pin;
}


void spindleOnCW(void) {
    
    pinSet(GPIOA, GPIO_BSRR_BS0);
}

void spindleOnCCW(void) {
    
    pinSet(GPIOA, GPIO_BSRR_BS1);
}

void spindleOff(void) {
    
    pinReset(GPIOA, GPIO_BSRR_BS0);
    pinReset(GPIOA, GPIO_BSRR_BS1);
}


void coolant1On(void) {
    pinSet(GPIOB, GPIO_BSRR_BS5);
}

void coolant2On(void) {
    pinSet(GPIOB, GPIO_BSRR_BS6);
}

void coolantAllOff(void) {
    pinReset(GPIOB, GPIO_BSRR_BS5);
    pinReset(GPIOB, GPIO_BSRR_BS6);
}


void programEnd(void) {
    
    spindleOff();
    coolantAllOff();
}