#ifndef CSTANDBY_H
#define CSTANDBY_H
#include <gtkmm.h>
#include <pangomm/fontdescription.h>

class cStandby : public Gtk::Box
{
public:
    cStandby(int iterations, Pango::FontDescription *font_desc);
    virtual ~cStandby();
    void updateCounters();

protected:

private:
    Gtk::Label *label;
    int counter;
    int numberOfIterations;
};

#endif // CSTANDBY_H
