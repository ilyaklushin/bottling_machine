#include "coincounter.hpp"

 void inCoinCounter(){
     //std::cout << "Coin " << std::endl;
     inputCoinCounter++;
     sessioninputCoinCounter++;
     targetWaterCount = floor((inputCoinCounter/WaterCost))*PulsePerLiter;
     std::stringstream displayCoinCounter_stream;
     displayCoinCounter_stream << std::fixed << std::setprecision(0) << inputCoinCounter;
     displayCoinCounter=displayCoinCounter_stream.str();
     std::stringstream displayWaterCounter_stream;
     displayWaterCounter_stream << std::fixed << std::setprecision(1) << float(targetWaterCount)/PulsePerLiter;
     displayWaterCounter=displayWaterCounter_stream.str();
 }
 void addCoins(float coins){
    inputCoinCounter+=coins;
    //sessioninputCoinCounter+=coins;
    targetWaterCount = (inputCoinCounter/WaterCost)*PulsePerLiter;
    std::stringstream displayCoinCounter_stream;
    displayCoinCounter_stream << std::fixed << std::setprecision(0) << inputCoinCounter;
    displayCoinCounter=displayCoinCounter_stream.str();
    std::stringstream displayWaterCounter_stream;
    displayWaterCounter_stream << std::fixed << std::setprecision(1) << float(targetWaterCount)/PulsePerLiter;
    displayWaterCounter=displayWaterCounter_stream.str();
 }
