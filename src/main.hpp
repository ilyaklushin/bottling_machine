#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

#include <iostream> // std::cout, std::fixed
#include <thread> // std::thread
#include <string>
#include <libconfig.h++> // Library for processing configuration files
#include <wiringPi.h>  // Wiring Library for Raspberry Pi
#include <mcp23017.h>  // MCP23017 I2C GPIO Externder library
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
#include "src/cMaintenance.cpp"


//Values
const std::string prog_version = "3.03";
int machine_id = 0;
std::string auth_key = "";
std::string api_address = "";
std::string db_name;


bool minWater = false;
bool midWater = false;
bool maxWater = false;
int sensWater = 0;
int lastsensWater = 0;

bool btn = false;
bool lastbtn = false;
bool usebtn = false;
bool btn2 = false;
bool btn3 = false;
std::string displayButtons;
std::string displaySensors;

bool noWater = false;
bool lastnoWater = false;
bool usenoWater = false;
int tankLevel=0;

float WaterCost = 1.5;
int PulsePerLiter = 784;

extern std::string displayCoinCounter;
extern std::string displayWaterCounter;
int action=0;
bool gui_thanks=false;
bool maintenanceMode=false;
bool remote_controlMode=false;
extern bool relayPump;
bool relayFiltration=false;
bool solenoidLockOut=false;
extern long int sessionTimer;

unsigned int db_send_delay=30; //delay in seconds


#define minWaterPin         25
#define midWaterPin         24
#define maxWaterPin         23

#define btnPin              103
#define btn2Pin             102
#define btn3Pin             101
#define sensExt1Pin         115
#define sensExt2Pin         114
#define sensExt3Pin         113

#define relayFiltrationPin  106
#define relayPumpPin        107

#define solenoidLockPin     100

#define watchdogRxPin       1
#define watchdogTxPin       4

#endif // MAIN_HPP_INCLUDED
