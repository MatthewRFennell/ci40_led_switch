#include <stdio.h>
#include <stdbool.h>

/* This header file includes the LetMeCreate library which is necessary for the control of the switches and LEDs */
#include "letmecreate.h"

/* A static volatile variable is required since the callback fucntions can have no parameters passed to them */
static volatile bool running = true;

/* This function toggles the LEDs on or off depending on whether they are already on or off */
void led_toggle(void){
        /* A static variable is required to retain its value between invocations of the led_toggle function */
        static bool ledOn = false;

        if(ledOn){
                led_switch_off(ALL_LEDS);
                ledOn = false;
        }
        else{
                led_switch_on(ALL_LEDS);
                ledOn = true;
        }
}

/* This function is called when switch 2 is pressed. It exits the while(running) loop in main - causing the program to end */
static void end_program(void){
        running = false;
}

int main(void){
        /* Initialises the switches and LEDs using the LetMeCreate library */
        switch_init();
        led_init();
        
        /* The first parameter is the event for which a callback function will be triggered. The second is a pointer to the function that will run when the event occurs */
        switch_add_callback(SWITCH_1_PRESSED, led_toggle);
        switch_add_callback(SWITCH_2_PRESSED, end_program);
        
        /* running is true until switch 2 is pressed */
        while(running)
                ;
        /* The LEDs are no longer accessible by the program */
        led_release();
        /* Removes all of the callback functions */
        switch_release();
        
        return 0;
}
