#include "Measurement.h"

using namespace std;

Measurement::Measurement(double value, const Date &timestamp,
                         const string &sensor)
    : value(value), timestamp(timestamp), sensor(sensor) {}
