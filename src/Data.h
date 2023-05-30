#if ! defined ( DATA_H )
#define DATA_H

#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <cmath>
#include "Provider.h"
#include "Measurement.h"
#include "Sensor.h"
#include "Cleaner.h"
#include "Date.h"
#include "GPS.h"
#include "User.h"
#include "Attribute.h"
#include "GovernmentMember.h"
#include "Admin.h"


class Data{
public:
  Data();

  void Load_CSV();

  std::vector<Measurement> retrieve_data_around_aircleaner(std::string id, Date start, Date end);

  std::vector<std::pair<Sensor, double>> get_five_nearest_sensors(GPS coord);

  std::vector<Measurement> get_measures_of_sensor(std::string sensorId, Date start, Date end);

  std::vector<std::string> get_aircleaner_impact(std::string cleaner_id);

  std::vector<User>& getUsers();

  double calculerDistance(GPS coord1, GPS coord2);

  static bool comparerParDouble(const std::pair<Sensor, double>& paire1, const std::pair<Sensor, double>& paire2) ;


  Sensor getSensorById(std::string sensorId);

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
