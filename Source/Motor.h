#ifndef CLASS_MOTOR_H
#define CLASS_MOTOR_H

typedef struct motor{
    int motor_pin;
}Motor;

void Motor_construct(Motor* const p_this);
int Motor_getPin(const Motor* const p_this);
void Motor_setting(Motor* const p_this, int pin, int clock, int range);
void Motor_moving(Motor* const p_this, int pin);

#endif