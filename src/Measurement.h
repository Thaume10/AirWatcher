#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

#include "Date.h"

class Measurement{
public:
  Measurement();

  Measurement(double value, Date timestamp);

  double get_value();

  Date get_timestamp();

protected:
  double value;
  Date timestamp;
};
#endif
