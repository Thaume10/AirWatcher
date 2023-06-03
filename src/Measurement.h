#if !defined(MEASUREMENT_H)
#define MEASUREMENT_H

#include "Attribute.h"
#include "Date.h"
#include "Sensor.h"

class Measurement {
public:
    Measurement();

    Measurement(double value, const Date &timestamp, const std::string &sensor);

    double get_value() const { return value; }

    Date get_timestamp() const { return timestamp; }

    Attribute &get_attribute() { return attibute; }

    Sensor get_sensor() const { return sensor; }

protected:
    double value;
    Date timestamp;
    Attribute attibute;
    Sensor sensor;
};
#endif
