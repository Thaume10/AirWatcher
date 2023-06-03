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

void Data::Load_CSV() {
    ifstream fichier;

    // Sensors
    string temp;
    string sensor_id;
    double latitude = 0;
    double longitude = 0;
    fichier.open("data/sensors.csv");

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

    fichier.close();

    // Measurements
    fichier.open("data/measurements.csv");

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
        date.String_to_time(datestr);
        Measurement m(val, date, sensorid);
        m.get_attribute().set_id(attribute_id);
        measurements.push_back(m);
    }

    fichier.close();

    // Users
    set<User> userSet;

    fichier.open("data/users.csv");
    string user_id;

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
    fichier.close();

    // Cleaners
    fichier.open("data/cleaners.csv");
    string cleaner_id;
    string debut;
    string fin;
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
        dateDebut.String_to_time(debut);
        dateFin.String_to_time(fin);
        GPS pos(latitude, longitude);

        cleaner.set_timestamp_start(dateDebut);
        cleaner.set_timestamp_stop(dateFin);
        cleaner.set_coord(pos);
        cleaners.push_back(cleaner);
    }
    fichier.close();

    // Provider
    set<Provider> providerSet;

    fichier.open("data/providers.csv");
    string provider_id;

    while (!fichier.eof()) {
        getline(fichier, provider_id, ';');
        getline(fichier, cleaner_id, ';');
        fichier >> ws;

        Provider provider(user_id);
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
    fichier.close();

    users.resize(userSet.size());
    copy(userSet.begin(), userSet.end(), users.begin());
    providers.resize(providerSet.size());
    copy(providerSet.begin(), providerSet.end(), providers.begin());
}

vector<User> &Data::getUsers() { return Data::users; }

vector<Sensor> &Data::getSensors() { return Data::sensors; }

vector<Cleaner> &Data::getCleaners() { return Data::cleaners; }

vector<Measurement> &Data::getMeasurements() { return measurements; }

vector<Provider> &Data::getProviders() { return providers; }

bool Data::comparerParDouble(const pair<Sensor, double> &paire1,
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
                    make_pair(*it, calculerDistance(coord, it->get_coord())));
            }
        } else {
            sort(top5.begin(), top5.end(), comparerParDouble);
            if (!it->get_is_malfunctionning() &&
                top5[0].second > calculerDistance(coord, it->get_coord())) {
                top5.erase(top5.begin());
                top5.push_back(
                    make_pair(*it, calculerDistance(coord, it->get_coord())));
            }
        }
    }
    sort(top5.begin(), top5.end(), comparerParDouble);

    return top5;
}
//
double Data::calculerDistance(const GPS &coord1, const GPS &coord2) {
    double deltaX = coord2.get_latitude() - coord1.get_latitude();
    double deltaY = coord2.get_longitude() - coord1.get_longitude();
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}

vector<Measurement> Data::get_measurementsSensor(const string &sensorId) {
    vector<Measurement> list;
    for (const Measurement &element : getMeasurements()) {
        if (element.get_sensor().get_id() == sensorId) {
            list.push_back(element);
        }
    }
    return list;
}

vector<Measurement> Data::get_measures_of_sensor(const string &sensorId,
                                                 const Date &start,
                                                 const Date &end,
                                                 Date &proche) {
    vector<Measurement> result;
    vector<Measurement> list = get_measurementsSensor(sensorId);
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
        minap.String_to_time("2100-01-01  14:00:00");
        Date minav;
        minav.String_to_time("0001-01-01   14:00:00");
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
            if (it->get_timestamp().To_string() == min.To_string()) {
                result.push_back(*it);
            }
        }
    }
    return result;
}

Sensor Data::getSensorById(const string &sensorId) {
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    while (itDebut != itFin) {
        if (itDebut->get_id() == sensorId) {
            return *itDebut;
        }
        ++itDebut;
    }
    return Sensor("");
}
