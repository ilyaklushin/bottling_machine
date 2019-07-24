#ifndef DB_HPP_INCLUDED
#define DB_HPP_INCLUDED

#include <sqlite3.h>
#include <curl/curl.h>
#include <unistd.h>
#include "json/single_include/nlohmann/json.hpp"

bool busydb=false;
using json = nlohmann::json;
extern bool renew_cron;

#include "db.cpp"

#endif // DB_HPP_INCLUDED
