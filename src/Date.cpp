#include "Date.h"
#include <ctime>
#include <sstream>
using namespace std;

#include <chrono>
#include <iomanip>

Date::Date() {
    time = std::time(nullptr);
}

std::string Date::To_string() {
    ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Date::String_to_time(std::string time) {
    tm dt;
    istringstream ss {time};
    ss >> get_time(&dt, "%Y-%m-%d %H:%M:%S");
    this->time = mktime(&dt);
}

void Date::add_days(int d) {
    tm *ti = localtime(&time);
    ti->tm_mday += d;
    time = mktime(ti);
}
