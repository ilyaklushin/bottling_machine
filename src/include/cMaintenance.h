#ifndef CMAINTENANCE_H
#define CMAINTENANCE_H
#include <gtkmm.h>
#include <pangomm/fontdescription.h>
#include <iomanip>

using namespace std;

class cMaintenance : public Gtk::Box
{
public:
    cMaintenance(int *_tankLevel, bool *_max, bool *_mid, bool *_min, int *_in, int *_out,
	bool *_pumpRelay, bool *_filtrationRelay, bool *_cleaningRelay, bool *_heatingRelay, bool *_solenoidLock, bool *_coinValidatorPwr,
	float *_temperature, float *_coins, float *_waterCounter, string *_buttons, string *_sensorsExt, int *_rangingMod, bool *_watchDog, bool *_lastKeepalive, int *_machineId);
    virtual ~cMaintenance();
    void updateCounters();

protected:

private:
	Gtk::Label *lTankLevel;
	Gtk::Label *lMax;
	Gtk::Label *lMid;
	Gtk::Label *lMin;
	Gtk::Label *lIn;
	Gtk::Label *lOut;
	Gtk::Label *lPumpRelay;
	Gtk::Label *lFiltrationRelay;
	Gtk::Label *lCleaningRelay;
	Gtk::Label *lHeatingRelay;
	Gtk::Label *lSolenoidLock;
	Gtk::Label *lCoinValidatorPwr;
	Gtk::Label *lTemperature;
	Gtk::Label *lCoins;
	Gtk::Label *lWaterCounter;
	Gtk::Label *lButtons;
	Gtk::Label *lSensorsExt;
	Gtk::Label *lRangingMod;
	Gtk::Label *lWatchDog;
	Gtk::Label *lLastKeepalive;



    int *tankLevel, *in, *out, *rangingMod;
    bool *max, *mid, *min, *pumpRelay, *filtrationRelay, *cleaningRelay, *heatingRelay, *solenoidLock, *coinValidatorPwr, *watchDog, *lastKeepalive;
    float *temperature, *coins, *waterCounter;
    string *buttons, *sensorsExt;

    stringstream ss;
};

#endif // CMAINTENANCE_H