#if ! defined ( SENSOR_H )
#define SENSOR_H

#include <map>
#include <vector>
#include "Measurement.h"
#include "Device.h"

class Sensor : public Device{
public:
  Sensor();

  Sensor(std::string id);

  Sensor(std::string id, bool is_malfunctionning); //Au cas où un user pas trustworthy créee un sensor

  std::map<Sensor, double> scoring_similar_sensors();

  bool get_is_malfunctionning();

  std::vector<Measurement> get_measurements();

  void set_is_malfunctionning(bool malfunctionning);

  void add_measurement(Measurement measurement);
  
protected:
  bool is_malfunctionning;
  std::vector<Measurement> measurements;
};
#endif
