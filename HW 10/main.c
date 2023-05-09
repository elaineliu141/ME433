#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro

#include <stdio.h>

#include "ws2812b.h"
#include "nu32dip.h"
void blink(int iterations, int time_ns);

int main() {
    ws2812b_setup();
    
    int hue = 0;
    int numLEDs = 5;
    wsColor led_colors[numLEDs];
    
    while (1) {
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT()<24000){}
        for (int i = 0; i < numLEDs; i++) {
            led_colors[i] = HSBtoRGB((hue + 60*i) % 360, 0.5, 0.5);
        }
        ws2812b_setColor(led_colors, numLEDs);
        hue++;
        if (hue > 360) {
            hue = 0;
        }
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}