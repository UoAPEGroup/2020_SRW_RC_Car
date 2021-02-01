/*
 * interrupt.h
 *
 * Created: 19/01/2021 10:10:24 pm
 *  Author: Earlene
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void interrupt_init();

static volatile uint16_t interruptCount;
static volatile uint8_t consecutiveChange;
static volatile bool establishedConnection;

uint16_t returnInterruptCount();
void resetInterruptCount();

#endif /* INTERRUPT_H_ */