#if !defined(DATA_H)
#define DATA_H

#include "Admin.h"
#include "Attribute.h"
#include "Cleaner.h"
#include "Date.h"
#include "GPS.h"
#include "GovernmentMember.h"
#include "Measurement.h"
#include "Provider.h"
#include "Sensor.h"
#include "User.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

class Data {
public:
    Data();

    static void Load_CSV();

    static std::vector<Measurement>
    retrieve_data_around_aircleaner(const std::string &id, const Date &start,
                                    const Date &end);

    static std::vector<std::pair<Sensor, double>>
    get_five_nearest_sensors(const GPS &coord);

    static std::vector<Measurement>
    get_measures_of_sensor(const std::string &sensorId, const Date &start,
                           const Date &end, Date &proche);

    static std::vector<std::string>
    get_aircleaner_impact(const std::string &cleaner_id);

    static std::vector<User> &getUsers();

    static std::vector<Sensor> &getSensors();

    static std::vector<Cleaner> &getCleaners();

    static std::vector<Measurement> &getMeasurements();

    static std::vector<Measurement>
    get_measurementsSensor(const std::string &sensorId);
    static std::vector<Provider> &getProviders();

    static double calculerDistance(const GPS &coord1, const GPS &coord2);

    static Sensor getSensorById(const std::string &sensorId);

    static bool comparerParDouble(const std::pair<Sensor, double> &paire1,
                                  const std::pair<Sensor, double> &paire2);

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
