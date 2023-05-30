#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

#include "Date.h"
#include "Attribute.h"

class Measurement{
public:
  Measurement();

  Measurement(double value, Date timestamp);

  

   double get_value() const {
        return value;
    }

    Date get_timestamp() const {
        return timestamp;
    }

    Attribute &get_attribute() {
        return attibute;
    }
  

protected:
  double value;
  Date timestamp;
  Attribute attibute;
};
#endif
