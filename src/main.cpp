#include "main.hpp"
#include "db.hpp"
#include "coincounter.cpp"
#include "bottling.cpp"


void noWaterWait(){
    if (lastnoWater==false && noWater==true) {

    }
}

void renew(){
    for (;;){
        minWater=digitalRead(minWaterPin);
        midWater=digitalRead(midWaterPin);
        maxWater=digitalRead(maxWaterPin);
        btn=!digitalRead(btnPin);
        if(lastbtn!=btn && btn == true) {usebtn=!usebtn;}
        lastbtn=btn;
        std::cout << "dispW: " << displayWaterCounter << "dispC:" << displayCoinCounter << "Btn:" << digitalRead(btnPin) << endl;
        delay(250);
        //db_bottling_add(1, 2);
    }
}

void filtration (){
    sensWater=0;
    digitalWrite(CoinCounterPwrPin, minWater);
    if (minWater==true or botling==true) {noWater=false; noWaterWait();}
    else {noWater=true;}
    if (minWater==true){sensWater+=100;}
    if (midWater==false) {digitalWrite(relayFiltrationPin, 1);}
    else {sensWater+=10;}
    if (maxWater==true) {digitalWrite(relayFiltrationPin, 0); sensWater+=1;}
    if (sensWater!=lastsensWater){
        db_add_filtration(minWater, midWater, maxWater);
    }
    lastsensWater=sensWater;

}

void toserver (){
    for (;;){
        db_send();
        sleep(5);
    }
}

void run_gui(int *_state, string *_liter, string *_money)
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("com.watermachine.gui");

    GUI gui(_state, _liter, _money, 48, "Lato");

    app->run(gui);
}

void chst_gui(){
    for(;;){
        while(botling==true || gui_thanks==true){
            if(gui_thanks==true){
                action=2;
                delay(5000);
                action=0;
                gui_thanks=false;
            }
            else{action=1;}
            delay(50);
        }
        if(noWater==true){
        action=3;
        }
        else{action=0;}
        delay(50);
    }
}

void watchdog(){
    for(;;){
    delay(5);
    digitalWrite(watchdogTxPin, digitalRead(watchdogRxPin));
    }
}

int main(int argc, char* argv[]){

    std::cout << "Bottling vending machine controller v. " << prog_version << std::endl;
    std::cout << "Initializing" << std::endl;
    wiringPiSetup ();

    std::cout << "WatchDog Initializing" << std::endl;
    std::thread twatchdog(watchdog);
    pinMode (watchdogRxPin, INPUT);
    pinMode (watchdogTxPin, OUTPUT);
    delay(50);

    mcp23017Setup (100, 0x20);
    pinMode (minWaterPin, INPUT);
    pinMode (midWaterPin, INPUT);
    pinMode (maxWaterPin, INPUT);
    pinMode (btnPin, INPUT);
    pullUpDnControl (minWaterPin, PUD_DOWN);
    pullUpDnControl (midWaterPin, PUD_DOWN);
    pullUpDnControl (maxWaterPin, PUD_DOWN);
    pullUpDnControl (btnPin, PUD_UP);



    pinMode (relayFiltrationPin, OUTPUT);
    pinMode (relayPumpPin, OUTPUT);
    pullUpDnControl (relayFiltrationPin, PUD_DOWN);
    pullUpDnControl (relayPumpPin, PUD_DOWN);

    pullUpDnControl (inCoinCounterPin, PUD_DOWN);
    wiringPiISR (inCoinCounterPin, INT_EDGE_FALLING, inCoinCounter);
    pinMode (CoinCounterPwrPin, OUTPUT);

    pullUpDnControl (outWaterCounterPin, PUD_DOWN);
    wiringPiISR ( outWaterCounterPin, INT_EDGE_BOTH, outWaterCounter);

    std::cout << "OK" << std::endl;
    std::thread trenew(renew);
    std::thread ttoserver(toserver);

    std::thread trun_gui(run_gui, &action, &displayWaterCounter, &displayCoinCounter);
    std::thread tchst_gui(chst_gui);


    //inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter(); //debug

    for (;;){
        std::thread tfiltration(filtration);
        std::thread tbottling(bottling);

        std::cout << "Sen " << digitalRead(minWaterPin) << digitalRead(midWaterPin) << digitalRead(maxWaterPin) << std::endl;
        //std::cout << "inCoin " << inputCoinCounter << std::endl;
        std::cout << "outWater " << outputWaterCounter << "lastnoWater " << lastnoWater << "noWater " << noWater << std::endl;
        //std::cout << "btn " << btn << " lastbtn " << lastbtn << " usebtn " << usebtn << std::endl;
        //std::time_t timer;
        //std::time(&timer);
        //std::cout << std::asctime(std::localtime(&timer)) << std::endl;
        tbottling.join();
        tfiltration.join();
        delay(100);
    }

    return 0;
}
