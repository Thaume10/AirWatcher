#include "Data.h"
#include "Sensor.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

vector<User> Data::users;
vector<Sensor> Data::sensors;

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

  users.resize(userSet.size());
  std::copy(userSet.begin(), userSet.end(), users.begin());
}

vector<User>& Data::getUsers(){
  return Data::users;
}

vector<Sensor>& Data::getSensors(){
  return Data::sensors;
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
//
//
// vector<Measurement> get_measures_of_sensor(string sensorId,  Date start, Date end){
//     vector<Measurement> result;
//     Sensor sensor = getSensorById(sensorId);
//     vector<Measurement>::iterator itDebut = sensor.get_measurements().begin();
//     vector<Measurement>::iterator itFin = sensor.get_measurements().end();
//     for (auto it = itDebut; it != itFin; ++it) {
//         if(it->get_timestamp < end && it->get_timestamp>start){
//             result.push_back(*it);
//         }
//     }
//     return result;
// }
//
// Sensor getSensorById(string sensorId){
//     vector<Sensor>::iterator itDebut = sensors.begin();
//     vector<Sensor>::iterator itFin = sensors.end();
//     bool fin =false;
//     while (itDebut != itFin && !fin) {
//         if (itDebut->get_id() == sensorId) {
//             return *itDebut;
//         }
//         ++itDebut;
//     }
//     return Sensor();
// }



