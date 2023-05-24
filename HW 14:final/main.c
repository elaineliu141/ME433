#include <stdio.h>
#include "nu32dip.h"

int main() {
    NU32DIP_Startup();
    __builtin_disable_interrupts(); // step 2: disable interrupts
    T2CONbits.TCKPS = 4;     // Timer2 prescaler N=4 (1:4)
    PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 20 kHz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 4500;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 500;              // initialize before turning OC1 on; afterward it is read-only
    
    OC1CONbits.ON = 1;       // turn on OC1
    // initialize b7 pin as oc1
    RPB7Rbits.RPB7R  = 0b0101 ; //set b7 to OC1

    T2CONbits.ON = 1;        // turn on Timer2
    
    while(1){
      OC1RS = 7500; 
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 24000000) { ; } 

      //alternate ORS
      OC1RS = 4500;
      _CP0_SET_COUNT(0);
      while(_CP0_GET_COUNT() < 24000000) { ; } 
    }
    return 0;

}



