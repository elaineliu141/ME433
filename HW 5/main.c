#include "spi.h"
//main function
int main(){
  //initialize stuff
  //precalc all the vs
  initSPI();

  while(1){
    //voltage for sine wave v=vs[i], v= A*sin(2pi*t/sample rate) +B
    float f = sint(t);
    unsigned int sinewave = f;
    //math to make sinewave to 1023

    
    


    //volt for tri wave
    //send volt w spi


    //delay


  }


}

void create_wave (float v, char a_or_b){
    //[a_or_b 1 1 1 [10 bit voltage] 0 0]
    unsigned short t = 0;
    t = 0b111 << 12;
    unsigned char a_or_b; //this is 0b0 or 0b1
    t = t | (a_or_b << 15);

    //stick in v << asferger
    //send volt w spi

    CS = 0; //initialize LAT
    spi_io(t >> 8);
    spi_io(t);
    CS = 1;
} 