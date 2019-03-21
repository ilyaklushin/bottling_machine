#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

#include <iostream> // std::cout, std::fixed
#include <thread> // std::thread
#include <string>
#include <wiringPi.h>  // Wiring Library for Raspberry Pi
#include "coincounter.hpp"
#include "bottling.hpp"

#include <gtkmm.h>
#include <cmath>
#include <iomanip> // std::setprecision
#include <sstream> // std::stringstream


#include <GUI.h>
#include "src/GUI.cpp"
#include "src/cRun.cpp"
#include "src/cStandby.cpp"
#include "src/box_run.cpp"


//Values
const std::string prog_version = "3.00";

bool minWater = false;
bool midWater = false;
bool maxWater = false;
int sensWater = 0;
int lastsensWater = 0;

bool btn = false;
bool lastbtn = false;
bool usebtn = false;

bool noWater = false;
bool lastnoWater = false;
bool usenoWater = false;

float WaterCost = 1.5;
int PulsePerLiter = 784;

extern std::string displayCoinCounter;
extern std::string displayWaterCounter;
int action=0;
bool gui_thanks=false;

#define minWaterPin         25
#define midWaterPin         24
#define maxWaterPin         23

//#define btnPin              27
#define btnPin              9

#define relayFiltrationPin  29
#define relayPumpPin        28

#define watchdogRxPin       4
#define watchdogTxPin       1


#endif // MAIN_HPP_INCLUDED
