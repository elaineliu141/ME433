#include <stdio.h>
#include "nu32dip.h"

int main() {
    NU32DIP_Startup();
    T2CONbits.TCKPS = 16;     // Timer2 prescaler N=4 (1:4)
    PR2 = 1999;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 500;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 500;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1



    // initialize output pin as off
    // TRIS...
    // LAT...
    TRISBbits.TRISB6 = 0; //rp bit
    LATBbits.LATB6 = 0;

    return 0;
}

