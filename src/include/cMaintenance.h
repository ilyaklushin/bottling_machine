#ifndef CMAINTENANCE_H
#define CMAINTENANCE_H
#include <gtkmm.h>
#include <pangomm/fontdescription.h>

using namespace std;

class cMaintenance : public Gtk::Box
{
public:
    cMaintenance(int *_tankLevel, bool *_max);
    virtual ~cMaintenance();
    void updateCounters();

protected:

private:
    Gtk::Label *lTankLevel;
    Gtk::Label *lMax;
    int *tankLevel;
    bool *max;
};

#endif // CMAINTENANCE_H