#ifndef GUI_H
#define GUI_H
#include <gtkmm.h>
#include <pangomm/fontdescription.h>

#include "cRun.h"
#include "cStandby.h"
#include "cMaintenance.h"

using namespace std;

class GUI: public Gtk::Window
{
public:
    GUI(int *_state, string *_liter, string *_money,
        int *_tankLevel, bool *_max, bool *_mid, bool *_min, int *_in, int *_out,
        bool *_pumpRelay, bool *_filtrationRelay, bool *_cleaningRelay, bool *_heatingRelay, bool *_solenoidLock, bool *_coinValidatorPwr,
        float *_temperature, volatile float *_coins, float *_waterCounter, string *_buttons, string *_sensorsExt, int *_rangingMod, bool *_watchDog, bool *_lastKeepalive, int *_machineId,
        int font_size = 40,
        string fontFamily = "DejaVu Sans Ultra-Light");
    virtual ~GUI();

protected:

private:
	int *state; // 0-4

    int laststate;

    bool update();
    void change_box(Gtk::Box *b);
    void change_box(cRun *b);
    void change_box(cStandby *b);
    void change_box(cMaintenance *b);

    Gtk::Box *box_nowater;
    Gtk::Box *box_thanks;

    cRun *box_run;
    cStandby *box_standby;

    cMaintenance *box_maintenance;

};

#endif // GUI_H
