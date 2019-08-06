#ifndef DB_HPP_INCLUDED
#define DB_HPP_INCLUDED

#include <sqlite3.h>
#include <curl/curl.h>
#include <unistd.h>
#include "json/single_include/nlohmann/json.hpp"

bool busydb=false;
using json = nlohmann::json;
extern bool renew_cron;
extern void fetch_cron(int previous_id, bool previous_status);
bool last_keepalive=false;

#include "db.cpp"

#endif // DB_HPP_INCLUDED
