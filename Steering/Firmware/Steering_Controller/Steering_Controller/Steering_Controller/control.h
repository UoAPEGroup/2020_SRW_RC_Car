/*
 * control.h
 *
 * Created: 12/01/2021 6:45:52 p.m.
 *  Author: npat692
 */ 


#ifndef CONTROL_H_
#define CONTROL_H_

// OUTPUT PIN INITIALIZATION
void pin_init();

// MAIN READER FUNCTION
void read_data();

// READER AND SETTER FUNCTIONS
void set_direction();
void set_speed();
void set_turn_angle();
void manual_steering();

// SPEED CONTROL SETTER FUNCTIONS
void set_no_speed();
void set_low_speed();
void set_med_speed();
void set_high_speed();

// SPEED BITS
#define LOW_H (input_data & (1 << 0))
#define MED_H (input_data & (1 << 1))
#define HIGH_H (input_data & (1 << 2))

// DIRECTION BITS
#define BACKWARD_H (input_data & (1 << 3))

// TURN BITS
#define RIGHT_H (input_data & (1 << 4))
#define HALF_TURN_H (input_data & (1 << 5))
#define FULL_TURN_H (input_data & (1 << 6))

// Motor Controller
#define STATE_INT_H PORTC |= (1 << PC5)
#define STATE_INT_L PORTC &=~ (1 << PC5)

// STATE INTERRUPT TRIGGER
#define STATE_INT_TOGGLE PORTC ^= (1 << PC5)

#define DRT_FWD PORTC |= (1 << PC4)
#define DRT_BCK PORTC &=~ (1 << PC4)

#define SPD_0_H PORTC |= (1 << PC2)
#define SPD_0_L PORTC &=~ (1 << PC2)

#define SPD_1_H PORTC |= (1 << PC3)
#define SPD_1_L PORTC &=~ (1 << PC3)


#endif /* CONTROL_H_ */