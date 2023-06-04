#include <unordered_map>
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

    static std::unordered_map<std::string, User> &get_users();

    static std::unordered_map<std::string, Sensor> &get_sensors();

    static std::unordered_map<std::string, Cleaner> &get_cleaners();

    static std::vector<Measurement> &get_measurements();

    static std::vector<Measurement>
    get_measurements_sensor(const std::string &sensor_id);

    static std::unordered_map<std::string, Provider> &get_providers();

    static double calculer_distance(const GPS &coord1, const GPS &coord2);

    static Sensor get_sensor_by_id(const std::string &sensor_id);

    static bool comparer_par_double(const std::pair<Sensor, double> &paire1,
                                    const std::pair<Sensor, double> &paire2);

protected:
    static std::unordered_map<std::string, User> users;
    static std::unordered_map<std::string, Provider> providers;
    static std::unordered_map<std::string, GovernmentMember> government_members;
    static std::unordered_map<std::string, Admin> admins;
    static std::vector<Measurement> measurements;
    static std::unordered_map<std::string, Sensor> sensors;
    static std::unordered_map<std::string, Cleaner> cleaners;
    static std::unordered_map<std::string, Attribute> attributes;

    static void load_users_CSV();

    static void load_sensors_CSV();

    static void load_cleaners_CSV();

    static void load_measurements_CSV();

    static void load_providers_CSV();
};
#endif
