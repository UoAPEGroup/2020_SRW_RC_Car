/*
 * control.h
 *
 * Created: 12/01/2021 6:45:52 p.m.
 *  Author: npat692
 */ 


#ifndef CONTROL_H_
#define CONTROL_H_

#include "global.h"
#include "instructions_macros.h"
#include "uart.h"

void read_data(char input_data);

/*
void set_forward_left(char input_data);
*/

void set_direction();
void set_speed();
void set_turn_state();

void toggle_st_int();


void set_no_speed();
void set_low_speed();
void set_med_speed();
void set_high_speed();



#endif /* CONTROL_H_ */