#include "bottling.hpp"

  void outWaterCounter(){
      outputWaterCounter++;
  }

  void bottling_reset(){
      gui_thanks=true;
      db_bottling_add(sessionWaterCount, sessioninputCoinCounter);
      spill=false;
      usebtn=false;
      targetWaterCount=0;
      inputCoinCounter=0;
      sessioninputCoinCounter=0;
      botling=false;
}

void bottling(){
    while (inputCoinCounter > 0 && usenoWater==false){
        botling = true;
        outputWaterCounter = 0;
        std::stringstream displayCoinCounter_stream;
        displayCoinCounter_stream << std::fixed << std::setprecision(0) << inputCoinCounter;
        displayCoinCounter=displayCoinCounter_stream.str();
        std::stringstream displayWaterCounter_stream;
        displayWaterCounter_stream << std::fixed << std::setprecision(1) << float(targetWaterCount)/PulsePerLiter;
        displayWaterCounter=displayWaterCounter_stream.str();
        while (usebtn==true && targetWaterCount > 0.01*(PulsePerLiter/WaterCost)){
            std::cout << "outputWaterCounter " << outputWaterCounter << " targetWaterCount " << targetWaterCount << " sessionWaterCount " << sessionWaterCount << " inputCoinCounter " << inputCoinCounter << std::endl;
            spill=true;
            if (inputCoinCounter<targetWaterCount){
                digitalWrite(relayPumpPin, 1);
            }
            else{
                bottling_reset();
            }
            //outputWaterCounter+=5;
            targetWaterCount-=outputWaterCounter;
            sessionWaterCount+=outputWaterCounter;
            std::stringstream displayCoinCounter_stream;
            displayCoinCounter_stream << std::fixed << std::setprecision(0) << inputCoinCounter;
            displayCoinCounter=displayCoinCounter_stream.str();
            std::stringstream displayWaterCounter_stream;
            displayWaterCounter_stream << std::fixed << std::setprecision(1) << float(targetWaterCount)/PulsePerLiter;
            displayWaterCounter=displayWaterCounter_stream.str();
            inputCoinCounter-=((float)outputWaterCounter/PulsePerLiter)*WaterCost;
            outputWaterCounter=0;
            delay(50);
        }
        digitalWrite(relayPumpPin, 0);
        if (targetWaterCount < 0.25*(PulsePerLiter/WaterCost) && spill==true){
            bottling_reset();
        }
        delay(50);

    }
}
