#ifndef CRON_HPP_INCLUDED
#define CRON_HPP_INCLUDED

#include <curl/curl.h>
#include <unistd.h>

//bool busydb=false;
using json = nlohmann::json;
bool renew_cron=false;

#include "cron.cpp"

#endif // CRON_HPP_INCLUDED
