#include "spi.h"
#include "nu32dip.h"
#include <math.h>

#define pi 3.1415

unsigned short create_wave(int channel, float voltage);
float sin_wave(float t);
float tri_wave(float t);

int main(){

    //enable startups
    NU32DIP_Startup();
    initSPI();
    
    //initialize stuff
    unsigned short p; 
    float v, t;
    t = 0.0;
    unsigned char spi_return;

    
    while (1) {
        //precalc all the vs
        //math to make sinewave to 1023
        v = sin_wave(t);
        p = create_wave(0, v);
        
        LATAbits.LATA0 = 0;
        //send volt to spi
        spi_return = spi_io(p >> 8);
        spi_return = spi_io(p);

        //CS back to high
        LATAbits.LATA0 = 1; 
        
        //voltage for triangle wave
        v = tri_wave(t);
        p = create_wave(1, v);
        //send volt to spi
        LATAbits.LATA0 = 0; 
        spi_return = spi_io(p >> 8);
        spi_return = spi_io(p);
        LATAbits.LATA0 = 1; 
        
        //delay for 0.01s
        _CP0_SET_COUNT(0);
        while(_CP0_GET_COUNT() < 240000) {} 
        t += 0.01;
    }


}

//voltage for sine wave 
//v=vs[i], v= A*sin(2pi*t/sample rate) +B
float sin_wave(float t) {
    return 1.65*sin(2*pi*t)+1.65;
}

//voltage for triangular wave
// consulted https://stackoverflow.com/questions/28588292/is-there-a-triangle-wave-function#:~:text=y%20%3D%20abs((x%2B%2B,oscillating%20between%203%20and%200.
// to create triangular wave
float tri_wave(float t) {
    int n = 1;
    float ix = t - floor(t);
    if ( ix <= n/2){
        return 1.65*ix; //ampltidue of 1.65
    }
    else{
        return 1.65-1.65*ix; //lower sloper
    }
        
}

//bit created: [a_or_b 1 1 1 (10 bit voltage) 0 0]
unsigned short create_wave(int wave, float volt) {
    unsigned short p, check; 
    check = 1023*volt;
    p = wave << 12;
    p = p | (0b111 << 15);
    p = p | ((check) & 0b111111111111);
    
    return p;
}

