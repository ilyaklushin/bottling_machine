#ifndef GUI_H
#define GUI_H
#include <gtkmm.h>
//#include <gtkmm/image.h>
#include <pangomm/fontdescription.h>


#include <cRun.h>
#include <cStandby.h>

using namespace std;

class GUI: public Gtk::Window
{
public:
    GUI(int *_state, string *_liter, string *_money, int font_size = 40, string fontFamily = "DejaVu Sans Ultra-Light");
    virtual ~GUI();

protected:

private:
	int *state; // 0-3
    //string *liter;
    //string *money;

    int laststate;

	bool update();
    void change_box(Gtk::Box *b);
    void change_box(cRun *b);
    void change_box(cStandby *b);

    Gtk::Box *box_nowater;
    Gtk::Box *box_thanks;

    cRun *box_run;
    cStandby *box_standby;

};

#endif // GUI_H
