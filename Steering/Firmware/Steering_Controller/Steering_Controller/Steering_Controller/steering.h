/*
 * steering.h
 *
 * Created: 21/01/2021 11:22:18 am
 *  Author: npat692
 */ 


#ifndef STEERING_H_
#define STEERING_H_

void calibrate_steering();
void find_ref();
void set_reference_values();

void set_half_r_turn();
void set_full_r_turn();
void set_half_l_turn();
void set_full_l_turn();
void set_straight_turn();

void print_refs();

#endif /* STEERING_H_ */