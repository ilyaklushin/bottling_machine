#ifndef CRON_HPP_INCLUDED
#define CRON_HPP_INCLUDED

#include <curl/curl.h>
#include <unistd.h>
#include <sys/reboot.h>

//bool busydb=false;
using json = nlohmann::json;
bool renew_cron=false;
extern int write_config();
extern void addCoins(float coins);
extern void openSolenoidLock();

#include "cron.cpp"

#endif // CRON_HPP_INCLUDED
