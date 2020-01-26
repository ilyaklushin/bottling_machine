#include "bottling.hpp"

  void outWaterCounter(){
      outputWaterCounter++;
  }

  void bottling_reset(){
      gui_thanks=true;
      unsigned int sessionTimeStop=std::time(nullptr);
      db_add_bottling(float(sessionWaterCount)/PulsePerLiter, sessioninputCoinCounter, sessionTimeStop-sessionTimeStart, sessionTimeStop);
      spill=false;
      usebtn=false;
      sessionWaterCount=0;
      targetWaterCount=0;
      inputCoinCounter=0;
      sessioninputCoinCounter=0;
      sessionTimer=0;
      botling=false;
      lastbotling=false;
}

void bottling(){
    usebtn=false;
    while (inputCoinCounter > 0 && usenoWater==false){
        botling = true;
        if (lastbotling==false){
            sessionTimeStart=std::time(nullptr);
            sessionTimer=0;
            lastbotling=true;
            }
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
            sessionTimer=0;
            if (inputCoinCounter<targetWaterCount){
                relayPump=true;
                digitalWriteM(relayPumpPin, 1);
            }
            else{
                bottling_reset();
            }
            //outputWaterCounter+=5; //debug
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
        digitalWriteM(relayPumpPin, 0);
        if ((sessionTimer/1000) > 180){
            bottling_reset();
        }
        if (targetWaterCount < 0.25*(PulsePerLiter/WaterCost) && spill==true){
            bottling_reset();
        }
        sessionTimer+=50;
        delay(50);

    }
}
