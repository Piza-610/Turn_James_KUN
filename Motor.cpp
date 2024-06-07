#include <iostream>
#include <wiringPi.h>
#include "Motor.h"

void Motor_construct(Motor* const p_this){
    p_this -> motor_pin = 19;
}

int Motor_getPin(const Motor* const p_this){
    return p_this -> motor_pin;
}

void Motor_setting(Motor* const p_this, int pin, int clock, int range){
    pinMode(pin, PWM_OUTPUT);   // (pin_num, mode) mode is output or input
    pwmSetMode(PWM_MODE_MS);    // change MarkSpace
    pwmSetClock(clock);
    pwmSetRange(range);
}

void Motor_moving(Motor* const p_this, int pin){
    std::cout << "Raspberry Pi wiringPi test program\n" << std::endl;

    pwmWrite(pin,150);  // (pin_num, output_val) 90°
    delay(2000);        // sleep
    //pwmWrite(pin, 200); // 180°
    //delay(1000);

}
