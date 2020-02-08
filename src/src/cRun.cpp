#include "../include/cRun.h"

cRun::cRun(string *_liters, string *_money, Pango::FontDescription *font_desc)
{
    liters = _liters;
    money = _money;

    lMoney = new Gtk::Label();
    lMoney->override_font(*font_desc);
    lMoney->set_xalign(1);

    lLiters = new Gtk::Label();
    lLiters->override_font(*font_desc);
    lLiters->set_xalign(1);
    // lLiters->set_margin_right(35);

    Gtk::Label *ltMoney = new Gtk::Label("На счету:");
    ltMoney->set_xalign(0);
    ltMoney->override_font(*font_desc);

    Gtk::Label *ltLiters = new Gtk::Label("Литры:");
    ltLiters->set_xalign(0);
    ltLiters->override_font(*font_desc);

    Gtk::Box * pPackBox1 = new Gtk::Box();
    pPackBox1->set_orientation(Gtk::ORIENTATION_VERTICAL);
    pPackBox1->pack_start(*ltMoney, Gtk::PACK_EXPAND_WIDGET);
    pPackBox1->pack_start(*ltLiters,Gtk::PACK_EXPAND_WIDGET);

    Gtk::Box * pPackBox2 = new Gtk::Box();
    pPackBox2->set_orientation(Gtk::ORIENTATION_VERTICAL);
    pPackBox2->pack_start(*lMoney, Gtk::PACK_EXPAND_WIDGET);
    pPackBox2->pack_start(*lLiters,Gtk::PACK_EXPAND_WIDGET);

    pack_start(*pPackBox1, Gtk::PACK_SHRINK, 10);
    pack_start(*pPackBox2, Gtk::PACK_EXPAND_WIDGET, 10);

    show_all();
}

cRun::~cRun()
{
    delete liters;
    delete money;

    delete lLiters;
    delete lMoney;
}

void cRun::updateCounters()
{
    lMoney->set_text(string(*money) + "₽");
    lLiters->set_text(string(*liters));
}
