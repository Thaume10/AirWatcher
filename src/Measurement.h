#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

#include "Date.h"

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

  

protected:
  double value;
  Date timestamp;
};
#endif
