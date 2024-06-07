#include <cstdio>     // printf()
#include <wiringPi.h> // wiringPiSetupGpio() pinMode() pwmSetMode() pwmSetRange() pwmSetClock() pwmWrite() delay()

int main(){
    int pin = 19;

    printf("Raspberry Pi wiringPi test program\n");
    wiringPiSetupGpio();        // clear WiringPi
    pinMode(pin, PWM_OUTPUT);   // (pin_num, mode) mode is output or input
    pwmSetMode(PWM_MODE_MS);    // change MarkSpace

    pwmSetClock(192);
    pwmSetRange(2000);

    while (true)
    {
        pwmWrite(pin,150);  // (pin_num, output_val) 90°
        delay(1000);        // sleep
        pwmWrite(pin, 200); // 180°
        delay(1000);
    }

    return 0;
}