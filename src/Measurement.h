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

    std::string get_attribute_id() const { return attribute_id; }

    void set_attribute_id(const std::string &attr_id) {
        attribute_id = attr_id;
    }

protected:
    double value;
    Date timestamp;
    std::string attribute_id;
};
#endif
