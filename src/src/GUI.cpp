#include "../include/GUI.h"

using namespace std;

GUI::GUI(int *_state, string *_liter, string *_money,
         int *_tankLevel, bool *_max, bool *_mid, bool *_min, int *_in, int *_out,
         bool *_pumpRelay, bool *_filtrationRelay, bool *_cleaningRelay, bool *_heatingRelay, bool *_solenoidLock, bool *_coinValidatorPwr,
         float *_temperature, float *_coins, float *_waterCounter, string *_buttons, string *_sensorsExt, int *_rangingMod, bool *_watchDog, bool *_lastKeepalive, int *_machineId,
         int font_size,
         string fontFamily)
{
    state = _state;
    laststate = -1;

    int timeout_value = 50;
    sigc::slot<bool> slot_update = sigc::mem_fun(*this, &GUI::update);
    Glib::signal_timeout().connect(slot_update, timeout_value);

    set_default_size(480, 320);
    set_position(Gtk::WIN_POS_CENTER);

    set_events(Gdk::ALL_EVENTS_MASK);
    set_modal(true);
    auto display = get_display();
    auto window = get_window();
    display->get_default_seat()->grab(window, Gdk::SEAT_CAPABILITY_ALL, true);
    
    auto image_nowater = new Gtk::Image("NoWater.png");

    Pango::FontDescription *font_desc = new Pango::FontDescription();
    font_desc->set_family(fontFamily);
    font_desc->set_size(font_size * Pango::SCALE);
    font_desc->set_weight(Pango::WEIGHT_LIGHT);

    {
        Gtk::Label *label = new Gtk::Label("Нет\nводы");
        label->override_font(*font_desc);

        label->set_justify(Gtk::JUSTIFY_CENTER);

        box_nowater = new Gtk::Box();
        box_nowater->pack_start(*label);
        box_nowater->pack_start(*image_nowater);
        box_nowater->show_all();
    }

    {
        Gtk::Label *label = new Gtk::Label("Спасибо\nза покупку!");
        label->override_font(*font_desc);
        label->set_justify(Gtk::JUSTIFY_CENTER);

        box_thanks = new Gtk::Box();
        box_thanks->pack_start(*label);
        box_thanks->show_all();
    }

    box_run = new cRun(_liter, _money, font_desc);
    box_standby = new cStandby(100, font_desc);
    box_maintenance = new cMaintenance(
        _tankLevel, _max, _mid, _min, _in, _out, _pumpRelay,
        _filtrationRelay, _cleaningRelay, _heatingRelay, _solenoidLock, _coinValidatorPwr,
        _temperature, _coins, _waterCounter, _buttons, _sensorsExt, _rangingMod, _watchDog, _lastKeepalive, _machineId,
        fontFamily
        );

}

GUI::~GUI()
{
    delete state;
    delete box_nowater;
    delete box_thanks;
    delete box_standby;
    delete box_run;
    delete box_maintenance;
}

void GUI::change_box(Gtk::Box *b)
{
    this->remove();
    add(*b);
}
void GUI::change_box(cRun *b)
{
    this->remove();
    add(*b);
}
void GUI::change_box(cStandby *b)
{
    this->remove();
    add(*b);
}
void GUI::change_box(cMaintenance *b)
{
    this->remove();
    add(*b);
}

bool GUI::update()
{
    box_run->updateCounters();
    box_standby->updateCounters();
    box_maintenance->updateCounters();

    if (laststate == *state) return true;
    laststate = *state;

    switch(*state)
    {
		case 1:
		{
			this->change_box(box_run);
			break;
		}
		case 2:
		{
			this->change_box(box_thanks);
			break;
		}
        case 3:
        {
            this->change_box(box_nowater);
            break;
        }
        case 4:
        {
            this->change_box(box_maintenance);
            break;
        }
		default:
		{
			this->change_box(box_standby);
			break;
		}
    }

    return true;
}
