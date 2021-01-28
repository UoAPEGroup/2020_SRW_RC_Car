/*
 * global.h
 *
 * Created: 18/01/2021 10:58:10 am
 *  Author: npat692
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

#define F_CPU 8000000UL
#define VREF 5000
#define ADC_RES 1024

#define K_P 0.8
#define K_I 1

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#endif /* GLOBAL_H_ */