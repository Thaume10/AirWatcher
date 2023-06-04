#include "Data.h"

#include <cmath>

#include "Sensor.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

vector<User> Data::users;
vector<Sensor> Data::sensors;
vector<Cleaner> Data::cleaners;
vector<Measurement> Data::measurements;
vector<Provider> Data::providers;

Data::Data() {}

void Data::load_users_CSV() {
    // Users
    set<User> userSet;

    ifstream fichier("data/users.csv");
    string user_id;
    string sensor_id;

    while (!fichier.eof()) {
        getline(fichier, user_id, ';');
        getline(fichier, sensor_id, ';');
        fichier >> ws;

        User user(user_id);
        Sensor sensor(sensor_id);

        auto it = find_if(sensors.begin(), sensors.end(), [&](const Sensor &s) {
            return s.get_id() == sensor_id;
        });

        if (it != sensors.end()) {
            GPS pos = it->get_coord();
            sensor.set_coord(pos);
        }

        set<User>::iterator itUser = userSet.find(user);
        if (itUser != userSet.end()) {
            user = *itUser;
        }
        user.add_sensor(sensor);
        userSet.erase(user);
        userSet.insert(user);
    }
    users.resize(userSet.size());
    copy(userSet.begin(), userSet.end(), users.begin());
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
        sensors.push_back(sensor);
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
        cleaners.push_back(cleaner);
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
        Measurement m(val, date, sensorid);
        m.get_attribute().set_id(attribute_id);
        measurements.push_back(m);
    }
}

void Data::load_providers_CSV() {
    // Provider
    set<Provider> providerSet;

    ifstream fichier("data/providers.csv");
    string provider_id;
    string cleaner_id;

    while (!fichier.eof()) {
        getline(fichier, provider_id, ';');
        getline(fichier, cleaner_id, ';');
        fichier >> ws;

        Provider provider(provider_id);
        Cleaner cleaner(cleaner_id);

        auto it =
            find_if(cleaners.begin(), cleaners.end(),
                    [&](const Cleaner &c) { return c.get_id() == cleaner_id; });

        if (it != cleaners.end()) {
            GPS pos = it->get_coord();
            cleaner.set_coord(pos);
            cleaner.set_timestamp_start(it->get_timestamp_start());
            cleaner.set_timestamp_stop(it->get_timestamp_stop());
        }

        set<Provider>::iterator itProvider = providerSet.find(provider);
        if (itProvider != providerSet.end()) {
            provider = *itProvider;
        }
        provider.add_cleaner(cleaner);
        providerSet.erase(provider);
        providerSet.insert(provider);
    }

    providers.resize(providerSet.size());
    copy(providerSet.begin(), providerSet.end(), providers.begin());
}

void Data::load_CSV() {
    load_users_CSV();
    load_sensors_CSV();
    load_cleaners_CSV();
    load_providers_CSV();
    load_measurements_CSV();
}

vector<User> &Data::get_users() { return Data::users; }

vector<Sensor> &Data::get_sensors() { return Data::sensors; }

vector<Cleaner> &Data::get_cleaners() { return Data::cleaners; }

vector<Measurement> &Data::get_measurements() { return measurements; }

vector<Provider> &Data::get_providers() { return providers; }

bool Data::comparer_par_double(const pair<Sensor, double> &paire1,
                               const pair<Sensor, double> &paire2) {
    return paire1.second > paire2.second;
}

vector<pair<Sensor, double>> Data::get_five_nearest_sensors(const GPS &coord) {
    vector<pair<Sensor, double>> top5;
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    for (auto it = itDebut; it != itFin; ++it) {
        if (top5.size() < 5) {
            if (!it->get_is_malfunctionning()) {
                top5.push_back(
                    make_pair(*it, calculer_distance(coord, it->get_coord())));
            }
        } else {
            sort(top5.begin(), top5.end(), comparer_par_double);
            if (!it->get_is_malfunctionning() &&
                top5[0].second > calculer_distance(coord, it->get_coord())) {
                top5.erase(top5.begin());
                top5.push_back(
                    make_pair(*it, calculer_distance(coord, it->get_coord())));
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
    vector<Measurement> list;
    for (const Measurement &element : get_measurements()) {
        if (element.get_sensor().get_id() == sensor_id) {
            list.push_back(element);
        }
    }
    return list;
}

vector<Measurement> Data::get_measures_of_sensor(const string &sensor_id,
                                                 const Date &start,
                                                 const Date &end,
                                                 Date &proche) {
    vector<Measurement> result;
    vector<Measurement> list = get_measurements_sensor(sensor_id);
    vector<Measurement>::iterator itDebut = list.begin();
    vector<Measurement>::iterator itFin = list.end();
    for (auto it = itDebut; it != itFin; ++it) {
        if (end > it->get_timestamp() && it->get_timestamp() > start) {
            result.push_back(*it);
        }
    }
    if (result.empty()) {
        // cout<<"No data in this period, the closest data available is :
        // "<<endl;

        Date minap;
        minap.string_to_time("2100-01-01  14:00:00");
        Date minav;
        minav.string_to_time("0001-01-01   14:00:00");
        for (auto it = itDebut; it != itFin; ++it) {
            Date diffBefore = start - minav;
            Date diffAfter = minap - end;
            if (it->get_timestamp() > end) {
                Date temp = it->get_timestamp() - end;
                if ((temp < diffAfter)) {
                    minap = it->get_timestamp();
                }
            } else if (it->get_timestamp() < start) {
                Date temp = start - it->get_timestamp();
                if (temp < diffBefore) {
                    minav = it->get_timestamp();
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
        for (auto it = itDebut; it != itFin; ++it) {
            if (it->get_timestamp().to_string() == min.to_string()) {
                result.push_back(*it);
            }
        }
    }
    return result;
}

Sensor Data::get_sensor_by_id(const string &sensor_id) {
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    while (itDebut != itFin) {
        if (itDebut->get_id() == sensor_id) {
            return *itDebut;
        }
        ++itDebut;
    }
    return Sensor("");
}
