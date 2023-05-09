#if ! defined ( DATA_H )
#define LECTURE_H

#include <fstream>
#include <vector>
#include <utility>
#include "User.h"
#include "Provider.h"
#include "GovernmentMember.h"
#include "Measurement.h"
#include "Admin.h"
#include "Sensor.h"
#include "Cleaner.h"
#include "Date.h"
#include "GPS.h"
#include "Attribute.h"


class Data{
public:
  Data();

  void Load_CSV();

  std::vector<Measurement> retrieve_data_around_aircleaner(std::string id, Date start, Date end);

  std::vector<std::pair<Sensor, int>> get_five_nearest_sensors(GPS coord);

  std::vector<Measurement> get_measures_of_sensor(std::string sensorId, Date start, Date end);

  std::vector<std::string> get_aircleaner_impact(std::string cleaner_id);

protected:
  std::vector<User> users;
  std::vector<Provider> providers;
  std::vector<GovernmentMember> government_members;
  std::vector<Admin> admins;
  std::vector<Measurement> measurements;
  std::vector<Sensor> sensors;
  std::vector<Cleaner> cleaners;
  std::vector<Attribute> attributes;
};
#endif
