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

  static void Load_CSV();

  static std::vector<Measurement> retrieve_data_around_aircleaner(std::string id, Date start, Date end);

  static std::vector<std::pair<Sensor, double>> get_five_nearest_sensors(GPS coord);

  static std::vector<Measurement> get_measures_of_sensor(std::string sensorId, Date start, Date end);

  static std::vector<std::string> get_aircleaner_impact(std::string cleaner_id);

  static std::vector<User>& getUsers();

  static std::vector<Sensor>& getSensors();

  static std::vector<Cleaner>& getCleaners();

  static double calculerDistance(GPS coord1, GPS coord2);

  static Sensor getSensorById(std::string sensorId);

  static bool comparerParDouble(const std::pair<Sensor, double>& paire1, const std::pair<Sensor, double>& paire2) ;

protected:
  static std::vector<User> users;
  static std::vector<Provider> providers;
  static std::vector<GovernmentMember> government_members;
  static std::vector<Admin> admins;
  static std::vector<Measurement> measurements;
  static std::vector<Sensor> sensors;
  static std::vector<Cleaner> cleaners;
  static std::vector<Attribute> attributes;
};
#endif
