#ifndef BOTTLING_HPP_INCLUDED
#define BOTTLING_HPP_INCLUDED

 volatile int outputWaterCounter = 0;
 volatile bool botling = false;
 volatile bool lastbotling = false;

 long int targetWaterCount = 0;
 long int sessionWaterCount = 0;
 long int sessionTimeStart = 0;
 bool spill = false;

std::string displayCoinCounter;
std::string displayWaterCounter;



#define outWaterCounterPin  21

#endif // BOTTLING_HPP_INCLUDED
