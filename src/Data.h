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

    static void load_CSV();

    static std::vector<Measurement>
    retrieve_data_around_aircleaner(const std::string &id, const Date &start,
                                    const Date &end);

    static std::vector<std::pair<Sensor, double>>
    get_five_nearest_sensors(const GPS &coord);

    static std::vector<Measurement>
    get_measures_of_sensor(const std::string &sensor_id, const Date &start,
                           const Date &end, Date &proche);

    static std::vector<std::string>
    get_aircleaner_impact(const std::string &cleaner_id);

    static std::vector<User> &get_users();

    static std::vector<Sensor> &get_sensors();

    static std::vector<Cleaner> &get_cleaners();

    static std::vector<Measurement> &get_measurements();

    static std::vector<Measurement>
    get_measurements_sensor(const std::string &sensor_id);

    static std::vector<Provider> &get_providers();

    static double calculer_distance(const GPS &coord1, const GPS &coord2);

    static Sensor get_sensor_by_id(const std::string &sensor_id);

    static bool comparer_par_double(const std::pair<Sensor, double> &paire1,
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

    static void load_users_CSV();

    static void load_sensors_CSV();

    static void load_cleaners_CSV();

    static void load_measurements_CSV();

    static void load_providers_CSV();
};
#endif
