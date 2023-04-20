//include files
#include "i2c_master_noint.h"
#include "nu32dip.h"

void turnOn_GP7(void);
unsigned char read_GP0(unsigned char address, unsigned char register1);
void generic_i2c_write(unsigned char address, unsigned char register1, unsigned char value);

int main() {
    //enable startups
    i2c_master_setup();
    NU32DIP_Startup();
    //init i2c chips
    //init the chip, GP0 is input, GP7 is output
    
    unsigned char sent = 0b0100000 << 1;
    unsigned char read;
    //blink gp7, turn on gp7, delay, turn off, delay
    while (1) {
        //blink yellow led
        turnOn_GP7();
        
        //r = read from GP0
        read = read_GP0(sent, 0x09);
        if (read) { //turn on GP0
            generic_i2c_write(sent, 0x0A, 0b10000000);
        }
        else { //turn off GP7
            generic_i2c_write(sent, 0x0A, 0b00000000);
        }
    }
}

//led
void turnOn_GP7(void) {
    LATAbits.LATA4 = !LATAbits.LATA4;
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 3000000) {}

    /*    testing yellow LED blink
    //write_i2c(0b01000000, 0xA, 0);
     _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 3000000) {}
    write_i2c(0b01000000, 0xA, 0b10000000); 

    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 3000000) {}*/
}

//read from GP0
unsigned char read_GP0(unsigned char address, unsigned char register1) {
    //send start bit
    i2c_master_start();
    //send addy w write bit
    i2c_master_send(address);
    //send reg u want to read from
    i2c_master_send(register1);
    //restart
    i2c_master_restart();
    //send addy w read bit
    i2c_master_send(address | 1);
    unsigned char r = (i2c_master_recv() & 0b00000001);
    //send ACK bit
    i2c_master_ack(1);
    //send stop bit
    i2c_master_stop();

    //just last bit
    return r;
}

//generic_i2c_write
void generic_i2c_write(unsigned char address, unsigned char register1, unsigned char value) {
    //start, send, addy/reg/value, stop
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(register1);
    i2c_master_send(value);
    i2c_master_stop();
}