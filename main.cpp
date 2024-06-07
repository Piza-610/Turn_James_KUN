#include <iostream>
#include <wiringPi.h> 
#include "Motor.h"

int main(){
    wiringPiSetupGpio();        // clear WiringPi

    Motor motor1;

    Motor_construct(&motor1);

    int pin = Motor_getPin(&motor1);

    Motor_setting(&motor1 , pin, 192, 2000);

    Motor_moving(&motor1 , pin);

    return 0;
}

// g++ -o Motor Turn_The_Neck/main.cpp Turn_The_Neck/Motor.cpp -lwiringPi
// sudo ./Motor
