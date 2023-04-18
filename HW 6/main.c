//include files
#include "i2c_master_noint.h"
#include "nu32dip.h"

void blink(void);
void write_i2c(unsigned char address, unsigned char registr, unsigned char value);
unsigned char read_i2c(unsigned char address, unsigned char registr);

int main() {

    i2c_master_setup();
    NU32DIP_Startup();
    
    unsigned char send_address = SLAVE_ADDRESS << 1;
    unsigned char rcvd;
    while (1) {
        blink();
        rcvd = read_i2c(send_address, GPIO);
        if (rcvd & 0b1 == 0b1) {
            write_i2c(send_address, OLAT, 0b10000000);
        }
        else {
            write_i2c(send_address, OLAT, 0b00000000);
        }
    }
}

void blink(void) {
    LATAbits.LATA4 = !LATAbits.LATA4;
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 3000000) {}
}

void write_i2c(unsigned char address, unsigned char registr, unsigned char value) {
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(registr);
    i2c_master_send(value);
    i2c_master_stop();
}

unsigned char read_i2c(unsigned char address, unsigned char registr) {
    unsigned char rcvd;
    i2c_master_start();
    i2c_master_send(address);
    i2c_master_send(registr);
    i2c_master_restart();
    i2c_master_send(address | 1);
    rcvd = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return rcvd;
}