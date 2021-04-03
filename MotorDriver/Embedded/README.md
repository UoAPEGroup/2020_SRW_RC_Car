# Motor Driver Embedded Side

The motor side embedded firmware controls the speed of the remote-controlled car by using PWM waves and an H-Bridge to variate the average voltage seen across the DC motor. Voltage at the H-Bridge, current at the H-Bridge, and motor power consumption data is sent to a live-updating website using BLE (bluetooth low energy) and an online PostGreSQL database. Safety features force the car to stop on over-voltage, over-current, and lost remote connection conditions.

## Features
- Uses an Atemga328PB to set the speed of the car between four set speeds [defined as STOP, MIN, MID, and MAX]
- Uses unipolar PWM modulation to change the duty cycle of PWM waves controlling the FETs in the H-Bridge
- Ramps voltage across motor at increments of 10 mV to prevent current spikes
- Switching frequency is 1.875kh
- Three safety paramaters cause the car to stop moving when triggered (at voltage > 20 V, current > 3 A, and if conenction to the remote controller team is lost)
- Connected to live-updating (voltage, current, and power data) website using BLE, python, and an online PostGreSQL database. See documentation here: ![link to software](https://github.com/UoAPEGroup/2020-srw-rc-car/blob/main/MotorDriver/Embedded/Software/README.md)


