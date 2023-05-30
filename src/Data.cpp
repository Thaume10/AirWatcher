#include "Data.h"
#include "Sensor.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

vector<User> Data::users;
vector<Sensor> Data::sensors;
vector<Cleaner> Data::cleaners;
vector<Measurement> Data::measurements;

Data::Data(){
}

void Data::Load_CSV(){
  ifstream fichier;

  //Sensors
  string temp;
  string sensor_id;
  double latitude;
  double longitude;
  fichier.open("data/sensors.csv");
  while(!fichier.eof()){
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

  //Measurements
  fichier.open("data/measurements.csv");
  while(!fichier.eof()){
    string datestr;
    string sensorid;
    string attribute_id;
    double val;
    getline(fichier, datestr, ';');
    getline(fichier, sensorid, ';');
    getline(fichier, attribute_id, ';');
    fichier >> val;
    string temp;
    getline(fichier, temp, ';');
    fichier >> ws;
    Date date;
    date.String_to_time(datestr);
    Measurement m(val, date);
    m.get_attribute().set_id(attribute_id);
    measurements.push_back(m);
  } 
  fichier.close();

  //Users
  std::set<User> userSet;

  fichier.open("data/users.csv");
  string user_id;

  while(!fichier.eof()){
    getline(fichier, user_id, ';');
    getline(fichier, sensor_id, ';');
    fichier >> ws;

    User user(user_id);
    Sensor sensor(sensor_id);

    auto it = std::find_if(sensors.begin(), sensors.end(), [&](const Sensor& s) {
      return s.get_id() == sensor_id;
    });

    if (it != sensors.end()) {
      GPS pos = it->get_coord();
      sensor.set_coord(pos);
    }

    set<User>::iterator itUser = userSet.find(user);
    if(itUser != userSet.end()){
      user = *itUser;
    }
    user.add_sensor(sensor);
    userSet.erase(user);
    userSet.insert(user);
  }
  fichier.close();

  //Cleaners
  fichier.open("data/cleaners.csv");
  string cleaner_id;
  string debut;
  string fin;
  while(!fichier.eof()){
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

  users.resize(userSet.size());
  std::copy(userSet.begin(), userSet.end(), users.begin());
}

vector<User>& Data::getUsers(){
  return Data::users;
}

vector<Sensor>& Data::getSensors(){
  return Data::sensors;
}

vector<Cleaner>& Data::getCleaners(){
  return Data::cleaners;
}

vector<Measurement>& Data::getMeasurements() {
    return measurements;
}

  bool Data::comparerParDouble(const std::pair<Sensor, double>& paire1, const std::pair<Sensor, double>& paire2) {
    return paire1.second > paire2.second;
}

vector<pair<Sensor, double>> Data::get_five_nearest_sensors(GPS coord){
    vector<pair<Sensor, double>> top5;
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    for (auto it = itDebut; it != itFin; ++it) {
        if(top5.size()<5){
            if(it->get_is_malfunctionning()==false){
                 top5.push_back(std::make_pair (*it,calculerDistance(coord,it->get_coord()) ));
            }
        }else{
            sort(top5.begin(), top5.end(), comparerParDouble);
            if(it->get_is_malfunctionning()==false && top5[0].second > calculerDistance(coord,it->get_coord())){
                top5.push_back(std::make_pair (*it,calculerDistance(coord,it->get_coord()) ));
            }
        }
        
    }
    return top5;
}
//
 double Data::calculerDistance(GPS coord1, GPS coord2) {
    double deltaX = coord2.get_latitude() - coord1.get_latitude();
    double deltaY = coord2.get_longitude() - coord1.get_longitude();
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}


vector<Measurement> Data::get_measures_of_sensor(string sensorId,  Date start, Date end){
    vector<Measurement> result;
    Sensor sensor = getSensorById(sensorId);
    vector<Measurement>::iterator itDebut = sensor.get_measurements().begin();
    vector<Measurement>::iterator itFin = sensor.get_measurements().end();
    for (auto it = itDebut; it != itFin; ++it) {
        if(it->get_timestamp() < end && it->get_timestamp()>start){
            result.push_back(*it);
        }
    }
    return result;
}

Sensor Data::getSensorById(string sensorId){
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    bool fin =false;
    while (itDebut != itFin && !fin) {
        if (itDebut->get_id() == sensorId) {
            return *itDebut;
        }
        ++itDebut;
    }
    return Sensor(nullptr);
}



