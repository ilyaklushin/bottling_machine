#ifndef WIRINGPIM_HPP_INCLUDED
#define WIRINGPIM_HPP_INCLUDED

#include <wiringPi.h>     // Wiring Library for Raspberry Pi
#include <mcp23017.h>     // MCP23017 I2C GPIO Externder library
#include <wiringPiI2C.h>  // WiringPi I2C functionality
#include <mutex>          // Mutex Lock

extern  int  digitalReadM           (int pin) ;
extern  void digitalWriteM          (int pin, int value) ;
extern  int  wiringPiI2CReadReg16M  (int fd, int reg) ;
extern  int  wiringPiI2CWriteReg16M (int fd, int reg, int data) ;

std::mutex wiringPiMLock;

#include "wiringPiM.cpp"

#endif // WIRINGPIM_HPP_INCLUDED
