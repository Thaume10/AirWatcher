#include "Data.h"

#include <cmath>

#include "Sensor.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, User> Data::users;
unordered_map<string, Sensor> Data::sensors;
unordered_map<string, Cleaner> Data::cleaners;
vector<Measurement> Data::measurements;
unordered_map<string, Provider> Data::providers;
unordered_map<string, Attribute> Data::attributes;

Data::Data() {}

void Data::load_users_CSV() {
    // Users

    ifstream fichier("data/users.csv");
    string user_id;
    string sensor_id;

    while (!fichier.eof()) {
        getline(fichier, user_id, ';');
        getline(fichier, sensor_id, ';');
        fichier >> ws;

        User user(user_id);
        auto itSensor = sensors.find(sensor_id);

        auto itUser = users.find(user_id);

        if (itUser != users.end()) {
            itUser->second.add_sensor(itSensor->second);
        } else {
            user.add_sensor(itSensor->second);
            users[user_id] = user;
        }
    }
}

void Data::load_attributes_CSV() {
    // Users

    ifstream fichier("data/attributes.csv");
    string attribute_id;
    string unit;
    string description;

    while (!fichier.eof()) {
        getline(fichier, attribute_id, ';');
        getline(fichier, unit, ';');
        getline(fichier, description, ';');
        fichier >> ws;

        Attribute attribute(attribute_id, unit, description);
        attributes[attribute_id] = attribute;
    }
}

void Data::load_sensors_CSV() {
    ifstream fichier("data/sensors.csv");

    // Sensors
    string temp;
    string sensor_id;
    double latitude = 0;
    double longitude = 0;

    while (!fichier.eof()) {
        getline(fichier, sensor_id, ';');
        fichier >> latitude;
        getline(fichier, temp, ';');
        fichier >> longitude;
        getline(fichier, temp, ';');
        fichier >> ws;

        Sensor sensor(sensor_id);

        GPS pos(latitude, longitude);

        sensor.set_coord(pos);
        sensors[sensor_id] = sensor;
    }
}

void Data::load_cleaners_CSV() {
    // Cleaners
    ifstream fichier("data/cleaners.csv");
    string cleaner_id;
    string debut;
    string fin;
    double latitude = 0;
    double longitude = 0;
    string temp;

    while (!fichier.eof()) {
        getline(fichier, cleaner_id, ';');
        fichier >> latitude;
        getline(fichier, temp, ';');
        fichier >> longitude;
        getline(fichier, temp, ';');
        getline(fichier, debut, ';');
        getline(fichier, fin, ';');
        fichier >> ws;

        Cleaner cleaner(cleaner_id);
        Date dateDebut;
        Date dateFin;
        dateDebut.string_to_time(debut);
        dateFin.string_to_time(fin);
        GPS pos(latitude, longitude);

        cleaner.set_timestamp_start(dateDebut);
        cleaner.set_timestamp_stop(dateFin);
        cleaner.set_coord(pos);
        cleaners[cleaner_id] = cleaner;
    }
}

void Data::load_measurements_CSV() {
    // Measurements
    ifstream fichier("data/measurements.csv");
    string temp;

    while (!fichier.eof()) {
        string datestr;
        string sensorid;
        string attribute_id;
        double val = 0;
        getline(fichier, datestr, ';');
        getline(fichier, sensorid, ';');
        getline(fichier, attribute_id, ';');
        fichier >> val;
        getline(fichier, temp, ';');
        fichier >> ws;
        Date date;
        date.string_to_time(datestr);
        Measurement m(val, date);
        m.set_attribute_id(attribute_id);
        measurements.push_back(m);
        sensors[sensorid].add_measurement(measurements.back());
    }
}

void Data::load_providers_CSV() {
    // Provider

    ifstream fichier("data/providers.csv");
    string provider_id;
    string cleaner_id;

    while (!fichier.eof()) {
        getline(fichier, provider_id, ';');
        getline(fichier, cleaner_id, ';');
        fichier >> ws;

        Provider provider(provider_id);

        auto itCleaner = cleaners.find(cleaner_id);

        auto itProvider = providers.find(provider_id);
        if (itProvider != providers.end()) {
            provider.add_cleaner(itCleaner->second);
        } else {
            provider.add_cleaner(itCleaner->second);
            providers[provider_id] = provider;
        }
    }
}

void Data::load_CSV() {
    load_attributes_CSV();
    load_sensors_CSV();
    load_cleaners_CSV();
    load_measurements_CSV();
    load_providers_CSV();
    load_users_CSV();
}

unordered_map<string, User> &Data::get_users() { return users; }

unordered_map<string, Sensor> &Data::get_sensors() { return Data::sensors; }

unordered_map<string, Cleaner> &Data::get_cleaners() { return Data::cleaners; }

vector<Measurement> &Data::get_measurements() { return measurements; }

unordered_map<string, Provider> &Data::get_providers() { return providers; }

bool Data::comparer_par_double(const pair<Sensor, double> &paire1,
                               const pair<Sensor, double> &paire2) {
    return paire1.second > paire2.second;
}

vector<pair<Sensor, double>> Data::get_five_nearest_sensors(const GPS &coord) {
    vector<pair<Sensor, double>> top5;

    for (const auto &it : sensors) {
        if (top5.size() < 5) {
            if (!it.second.get_is_malfunctionning()) {
                top5.push_back(
                    make_pair(it.second,
                              calculer_distance(coord, it.second.get_coord())));
            }
        } else {
            sort(top5.begin(), top5.end(), comparer_par_double);
            if (!it.second.get_is_malfunctionning() &&
                top5[0].second >
                    calculer_distance(coord, it.second.get_coord())) {
                top5.erase(top5.begin());
                top5.push_back(
                    make_pair(it.second,
                              calculer_distance(coord, it.second.get_coord())));
            }
        }
    }
    sort(top5.begin(), top5.end(), comparer_par_double);

    return top5;
}
//
double Data::calculer_distance(const GPS &coord1, const GPS &coord2) {
    double deltaX = coord2.get_latitude() - coord1.get_latitude();
    double deltaY = coord2.get_longitude() - coord1.get_longitude();
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

vector<Measurement> Data::get_measurements_sensor(const string &sensor_id) {
    return sensors[sensor_id].get_measurements();
}

vector<Measurement> Data::get_measures_of_sensor(const string &sensor_id,
                                                 const Date &start,
                                                 const Date &end,
                                                 Date &proche) {
    vector<Measurement> result;
    vector<Measurement> measures = get_measurements_sensor(sensor_id);
    for (const auto &measure : measures) {
        if (end > measure.get_timestamp() && measure.get_timestamp() > start) {
            result.push_back(measure);
        }
    }
    if (result.empty()) {
        // cout<<"No data in this period, the closest data available is :
        // "<<endl;

        Date minap;
        minap.string_to_time("2100-01-01  14:00:00");
        Date minav;
        minav.string_to_time("0001-01-01   14:00:00");
        for (const auto &measure : measures) {
            Date diffBefore = start - minav;
            Date diffAfter = minap - end;
            if (measure.get_timestamp() > end) {
                Date temp = measure.get_timestamp() - end;
                if ((temp < diffAfter)) {
                    minap = measure.get_timestamp();
                }
            } else if (measure.get_timestamp() < start) {
                Date temp = start - measure.get_timestamp();
                if (temp < diffBefore) {
                    minav = measure.get_timestamp();
                }
            }
        }
        Date diffBefore = start - minav;
        Date diffAfter = minap - end;
        Date min;
        if (diffAfter < diffBefore) {
            min = minap;
        } else {
            min = minav;
        }
        proche = min;
        for (const auto &measure : measures) {
            if (measure.get_timestamp().to_string() == min.to_string()) {
                result.push_back(measure);
            }
        }
    }
    return result;
}

Sensor Data::get_sensor_by_id(const string &sensor_id) {
    auto it = sensors.find(sensor_id);
    if (it != sensors.end()) {
        return it->second;
    }
    return Sensor("");
}
