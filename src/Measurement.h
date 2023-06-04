#if !defined(MEASUREMENT_H)
#define MEASUREMENT_H

#include "Attribute.h"
#include "Date.h"

class Measurement {
public:
    Measurement();

    Measurement(double value, const Date &timestamp);

    double get_value() const { return value; }

    Date get_timestamp() const { return timestamp; }

    Attribute &get_attribute() { return attibute; }

protected:
    double value;
    Date timestamp;
    Attribute attibute;
};
#endif
