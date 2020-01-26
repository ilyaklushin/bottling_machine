#include "wiringPiM.hpp"

int digitalReadM (int pin){
    wiringPiMLock.lock();
    int temp;
    temp=digitalRead(pin);
    wiringPiMLock.unlock();
    return temp;
}

void digitalWriteM (int pin, int value){
    wiringPiMLock.lock();
    digitalWrite(pin, value);
    wiringPiMLock.unlock();
}

int  wiringPiI2CReadReg16M (int fd, int reg){
    wiringPiMLock.lock();
    int temp;
    temp=wiringPiI2CReadReg16(fd, reg);
    wiringPiMLock.unlock();
    return temp;
}

int  wiringPiI2CWriteReg16M (int fd, int reg, int data){
    wiringPiMLock.lock();
    int temp;
    temp=wiringPiI2CWriteReg16(fd, reg, data);
    wiringPiMLock.unlock();
    return temp;
}
