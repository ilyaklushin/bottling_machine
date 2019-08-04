#ifndef CMAINTENANCE_H
#define CMAINTENANCE_H
#include <gtkmm.h>
#include <pangomm/fontdescription.h>

using namespace std;

class cMaintenance : public Gtk::Box
{
public:
    cMaintenance(string *_liters, string *_money, Pango::FontDescription *font_desc);
    virtual ~cMaintenance();
    void updateCounters();

protected:

private:
    Gtk::Label *lMoney;
    Gtk::Label *lLiters;
    string *liters;
    string *money;
};

#endif // CMAINTENANCE_H