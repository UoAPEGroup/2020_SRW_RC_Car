/*
 * pi_controller.h
 *
 * Created: 28/01/2021 4:18:25 pm
 *  Author: npat692
 */ 


#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_

void pi_setup();
void pi_controller();
int16_t compute_pi(uint16_t input);

#endif /* PI_CONTROLLER_H_ */