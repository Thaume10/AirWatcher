#include "Date.h"
#include <sstream>
using namespace std;

#include <chrono>
#include <iomanip>

Date::Date() {
    time = std::time(nullptr);
}

std::string Date::To_string() {
    ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%d-%m-%Y %H-%M-%S");
    return oss.str();
}

