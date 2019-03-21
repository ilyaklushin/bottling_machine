#ifndef CRUN_H
#define CRUN_H
#include <gtkmm.h>
#include <pangomm/fontdescription.h>

using namespace std;

class cRun : public Gtk::Box
{
public:
    cRun(string *_liters, string *_money, Pango::FontDescription *font_desc);
    virtual ~cRun();
    void updateCounters();

protected:

private:
    Gtk::Label *lMoney;
    Gtk::Label *lLiters;
    string *liters;
    string *money;
};

#endif // CRUN_H
