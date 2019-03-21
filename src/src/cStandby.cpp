#include "cStandby.h"

cStandby::cStandby(int iterations, Pango::FontDescription *font_desc)
{
    counter = 0;
    numberOfIterations = iterations;
    label = new Gtk::Label("Внесите\nналичные");
    label->override_font(*font_desc);
    label->set_justify(Gtk::JUSTIFY_CENTER);
    pack_start(*label, Gtk::PACK_EXPAND_WIDGET, 10);
    show_all();
}

cStandby::~cStandby()
{
    delete label;
}

void cStandby::updateCounters()
{
    counter++;
    if (counter <= numberOfIterations) return;

    if(label->get_text() == "Внесите\nналичные") label->set_text("Повесьте\nёмкость");
    else label->set_text("Внесите\nналичные");
    counter = 0;
}
