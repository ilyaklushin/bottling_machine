#include "GUI.h"

using namespace std;

GUI::GUI(int *_state, string *_liter, string *_money, int font_size, string fontFamily)
{
    state = _state;
    laststate = 11; // do not touch!!!!!!!!!!!!!!!!!!!!!

    int timeout_value = 50;
    sigc::slot<bool> slot_update = sigc::mem_fun(*this, &GUI::update);
    Glib::signal_timeout().connect(slot_update, timeout_value);

    set_default_size(480, 320);
    //fullscreen();
    set_position(Gtk::WIN_POS_CENTER);

    //set_events(Gdk::EXPOSURE_MASK | Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK | Gdk::BUTTON_MOTION_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON2_MOTION_MASK | Gdk::BUTTON3_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK | Gdk::ENTER_NOTIFY_MASK | Gdk::FOCUS_CHANGE_MASK | Gdk::STRUCTURE_MASK | Gdk::PROPERTY_CHANGE_MASK | Gdk::VISIBILITY_NOTIFY_MASK | Gdk::PROXIMITY_IN_MASK | Gdk::PROXIMITY_OUT_MASK | Gdk::SUBSTRUCTURE_MASK | Gdk::SCROLL_MASK | Gdk::TOUCH_MASK | Gdk::SMOOTH_SCROLL_MASK | Gdk::TOUCHPAD_GESTURE_MASK);
    set_events(Gdk::ALL_EVENTS_MASK);
    set_modal(true);
    auto display = get_display();
    auto window = get_window();
    auto grabSuccess = display->get_default_seat()->grab(window, Gdk::SEAT_CAPABILITY_ALL, true);

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
    box_standby = new cStandby(100,font_desc);

}

GUI::~GUI()
{
    delete state;
    delete box_nowater;
    delete box_thanks;
    delete box_standby;
    delete box_run;
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

bool GUI::update()
{
    box_run->updateCounters();
    box_standby->updateCounters();

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
		default:
		{
			this->change_box(box_standby);
			break;
		}
    }

    return true;
}
