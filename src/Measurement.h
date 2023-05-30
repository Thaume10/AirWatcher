#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

#include "Date.h"
#include "Attribute.h"

class Measurement{
public:
  Measurement();

  Measurement(double value, Date timestamp);

  

  inline double get_value() const {
        return value;
    }

    inline Date get_timestamp() const {
        return timestamp;
    }

    inline Attribute get_attribute() const {
        return attibute;
    }
  

protected:
  double value;
  Date timestamp;
  Attribute attibute;
};
#endif
