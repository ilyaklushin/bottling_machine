#include "main.hpp"
#include "wiringPiM.hpp"
#include "db.hpp"
#include "cron.hpp"
#include "coincounter.cpp"
#include "bottling.cpp"

using namespace libconfig;

auto read_config(){
    Config cfg;
    try{
        cfg.readFile("machine.cfg");
    }
    catch(const FileIOException &fioex){
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const ParseException &pex){
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    std::cout << "Config found" << std::endl;
    try{
        machine_id = cfg.lookup("machine_id");
        std::cout << "Store machine id: " << machine_id << std::endl;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "No 'machine_id' setting in configuration file." << std::endl;
    }
    try{
        auth_key = cfg.lookup("auth_key").c_str();
        std::cout << "Store auth_key: " << auth_key << std::endl;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "No 'auth_key' setting in configuration file." << std::endl;
    }
    try{
        WaterCost = cfg.lookup("water_cost");
        std::cout << "Store water cost: " << WaterCost << std::endl;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "No 'water_cost' setting in configuration file." << std::endl;
    }
    try{
        PulsePerLiter = cfg.lookup("pulse_per_liter");
        std::cout << "Store pulse per liter: " << PulsePerLiter << std::endl;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "No 'pulse_per_liter' setting in configuration file." << std::endl;
    }
    try{
        api_address = cfg.lookup("api_address").c_str();
        std::cout << "Store api address: " << api_address << std::endl;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "No 'api address' setting in configuration file." << std::endl;
    }
    try{
        db_name = cfg.lookup("db_name").c_str();
        std::cout << "Store db name: " << db_name << std::endl;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "No 'db_name' setting in configuration file." << std::endl;
    }
}

int write_config(){
    Config cfg;
    try{
        cfg.readFile("machine.cfg");
    }
    catch(const FileIOException &fioex){
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const ParseException &pex){
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    try{
        Setting &l_machine_id = cfg.lookup("machine_id");
        Setting &l_auth_key = cfg.lookup("auth_key");
        Setting &l_WaterCost = cfg.lookup("water_cost");
        Setting &l_PulsePerLiter = cfg.lookup("pulse_per_liter");
        Setting &l_api_address = cfg.lookup("api_address");
        Setting &l_db_name = cfg.lookup("db_name");

        l_machine_id = machine_id;
        l_auth_key = auth_key;
        l_WaterCost = WaterCost;
        l_PulsePerLiter = PulsePerLiter;
        l_api_address = api_address;
        l_db_name = db_name;

        cfg.writeFile("machine.cfg");
        return 1;
    }
    catch(const SettingNotFoundException &nfex){
        std::cerr << "Some settings not found in configuration file, while trying write configuration file." << std::endl;
        return 0;
    }
}

void openSolenoidLock(){
    solenoidLockOut=true;
    digitalWriteM(solenoidLockPin, 1);
    sleep(5);
    solenoidLockOut=false;
    digitalWriteM(solenoidLockPin, 0);
}

void noWaterWait(){
    if (lastnoWater==false && noWater==true) {

    }
}

void renew(){
    for (;;){
        minWater=digitalReadM(minWaterPin);
        midWater=digitalReadM(midWaterPin);
        maxWater=digitalReadM(maxWaterPin);
        btn=!digitalReadM(btnPin);
        if(lastbtn!=btn && btn == true) {usebtn=!usebtn;}
        lastbtn=btn;
        btn2=!digitalReadM(btn2Pin);
        btn3=!digitalReadM(btn3Pin);
        displayButtons = std::to_string(btn) + std::to_string(btn2) + std::to_string(btn3);
        displaySensors = std::to_string(digitalReadM(sensExt1Pin)) + std::to_string(digitalReadM(sensExt2Pin)) + std::to_string(digitalReadM(sensExt3Pin));
        //std::cout << "dispW: " << displayWaterCounter << "dispC:" << displayCoinCounter << "Btn:" << digitalReadM(btnPin) << "sTr:"<< sessionTimer << endl;
        delay(250);
        //db_bottling_add(1, 2);
    }
}

void filtration (){
    sensWater=0;
    digitalWriteM(CoinCounterPwrPin, minWater);
    if (minWater==true or botling==true) {noWater=false; noWaterWait();}
    else {noWater=true;}
    if (minWater==true){sensWater+=100;}
    if (midWater==false) {digitalWriteM(relayFiltrationPin, 1); relayFiltration=true;}
    else {sensWater+=10;}
    if (maxWater==true) {digitalWriteM(relayFiltrationPin, 0); sensWater+=1; relayFiltration=false;}
    if (sensWater!=lastsensWater){
        db_add_filtration(minWater, midWater, maxWater);
    }
    lastsensWater=sensWater;

}

void toserver (){
    for (;;){
        db_send();
        sleep(db_send_delay);
    }
}

void sensors_refresh(){
    for (;;){
        phSensor0_avg=wiringPiI2CReadReg16M(i2c_slave0, 'A');
        int16_t Sensor1_avg=wiringPiI2CReadReg16M(i2c_slave0, 'B');
        int16_t Sensor2_avg=wiringPiI2CReadReg16M(i2c_slave0, 'C');
        int16_t Counter0_avg=wiringPiI2CReadReg16M(i2c_slave0, 'J');
        int16_t Counter1_avg=wiringPiI2CReadReg16M(i2c_slave0, 'K');
        in_flow_avg=Counter0_avg/784;
        tank_flow_avg=Counter1_avg/784;
        in_pressure_avg=((3.0*((float)((Sensor1_avg*5.0)/1024.0)-0.500))*1000000.0)/10e5;
        membrane_pressure_avg=((3.0*((float)((Sensor2_avg*5.0)/1024.0)-0.500))*1000000.0)/10e5;
        db_add_sensors(phSensor0_avg, in_flow_avg, tank_flow_avg, in_pressure_avg, membrane_pressure_avg);
        std::cout << "I2CREG " << Sensor1_avg << " " << Sensor2_avg << " " << Counter0_avg << " " << Counter1_avg << " " << std::endl;
        sleep(60);
    }
}

void run_gui(int *_state, string *_liter, string *_money, int *_tankLevel )
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("com.watermachine.gui");
  int in = 25;
  int out = 250;

  bool cleaningRelay = false;
  bool heatingRelay = false;
  bool *coinValidatorPwr = &minWater;
  float temperature = 21.5;
  float WaterCounterRate = 00.0;
  int rangingMod = 10;
  bool watchDog = true;

    GUI gui(_state, _liter, _money, _tankLevel, &maxWater, &midWater, &minWater, &in, &out, &relayPump, &relayFiltration, &cleaningRelay, &heatingRelay, &solenoidLockOut, coinValidatorPwr,
            &temperature, &inputCoinCounter, &WaterCounterRate, &displayButtons, &displaySensors, &rangingMod, &watchDog, &last_keepalive, &machine_id,  48, "Lato");

    app->run(gui);
}

void chst_gui(){
    for(;;){
        while((botling==true || gui_thanks==true) && maintenanceMode==false){
            if(gui_thanks==true){
                action=2;
                delay(5000);
                action=0;
                gui_thanks=false;
            }
            else{action=1;}
            delay(50);
        }
        if(noWater==true && maintenanceMode==false){action=3;}
        else if (maintenanceMode==true){action=4;}
        else{action=0;}
        delay(50);
    }
}

void watchdog(){
    for(;;){
    delay(5);
    digitalWriteM(watchdogTxPin, digitalReadM(watchdogRxPin));
    }
}

int main(int argc, char* argv[]){

    std::cout << "Bottling vending machine controller v. " << prog_version << std::endl;
    std::cout << "Initializing" << std::endl;
    wiringPiSetup ();
    if (read_config()==EXIT_FAILURE){return(EXIT_FAILURE);}

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
    pinMode (btn2Pin, INPUT);
    pinMode (btn3Pin, INPUT);
    pinMode (sensExt1Pin, INPUT);
    pinMode (sensExt2Pin, INPUT);
    pinMode (sensExt3Pin, INPUT);
    pullUpDnControl (minWaterPin, PUD_DOWN);
    pullUpDnControl (midWaterPin, PUD_DOWN);
    pullUpDnControl (maxWaterPin, PUD_DOWN);
    pullUpDnControl (btnPin, PUD_UP);
    pullUpDnControl (btn2Pin, PUD_UP);
    pullUpDnControl (btn3Pin, PUD_UP);

    pinMode (solenoidLockPin, OUTPUT);
    pullUpDnControl (solenoidLockPin, PUD_DOWN);
    pinMode (relayFiltrationPin, OUTPUT);
    pinMode (relayPumpPin, OUTPUT);
    pullUpDnControl (relayFiltrationPin, PUD_DOWN);
    pullUpDnControl (relayPumpPin, PUD_DOWN);

    pullUpDnControl (inCoinCounterPin, PUD_DOWN);
    wiringPiISR (inCoinCounterPin, INT_EDGE_FALLING, inCoinCounter);
    pinMode (CoinCounterPwrPin, OUTPUT);

    pullUpDnControl (outWaterCounterPin, PUD_DOWN);
    wiringPiISR ( outWaterCounterPin, INT_EDGE_BOTH, outWaterCounter);

    i2c_slave0 = wiringPiI2CSetup(0x05);

    std::cout << "OK" << std::endl;
    std::thread trenew(renew);
    std::thread ttoserver(toserver);
    std::thread tsensors(sensors_refresh);

    std::thread trun_gui(run_gui, &action, &displayWaterCounter, &displayCoinCounter, &tankLevel);
    std::thread tchst_gui(chst_gui);


    //inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter();inCoinCounter(); //debug

    for (;;){
        std::thread tfiltration(filtration);
        std::thread tbottling(bottling);

        //std::cout << "Sen " << digitalReadM(minWaterPin) << digitalReadM(midWaterPin) << digitalReadM(maxWaterPin) << std::endl;
        //std::cout << "inCoin " << inputCoinCounter << std::endl;
        //std::cout << "outWater " << outputWaterCounter << "lastnoWater " << lastnoWater << "noWater " << noWater << std::endl;
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
