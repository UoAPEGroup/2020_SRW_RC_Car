/*
 * interrupt.h
 *
 * Created: 19/01/2021 10:10:24 pm
 *  Author: Earlene
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void stChangeInterrupt_init();

static volatile uint16_t interruptCount;
static volatile uint8_t consecutiveChange;

uint16_t returnInterruptCount();
void resetInterruptCount();

void encoderInterrupt_init();

#endif /* INTERRUPT_H_ */