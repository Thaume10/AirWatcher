#include "Data.h"
#include "Sensor.h"
#include <fstream>
#include <iostream>

using namespace std;

Data::Data(){
  
}

void Data::Load_CSV(){
  ifstream fichier("data/users.csv");
  string user_id;
  string sensor_id;
  while(fichier){
    getline(fichier, user_id, ';');
    getline(fichier, sensor_id, ';');
    fichier >> ws;
    User user(user_id);
    Sensor sensor(sensor_id);
    cout << user_id << endl;
    cout << sensor_id << endl;
    user.add_sensor(sensor);
    users.push_back(user);
    sensors.push_back(sensor);
  }

}

 bool comparerParDouble(const std::pair<Sensor, double>& paire1, const std::pair<Sensor, double>& paire2) {
    return paire1.second > paire2.second;
}

vector<pair<Sensor, double>> get_five_nearest_sensors(GPS coord){
    vector<pair<Sensor, double>> top5;
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    for (auto it = itDebut; it != itFin; ++it) {
        if(top5.size()<5){
            if(it->get_is_malfunctionning()==false){
                 top5.push_back(*it);
            }
        }else{
            sort(top5.begin(), top5.end(), comparerParDouble);
            if(it->get_is_malfunctionning()==false && top5[0].second > calculerDistance(coord,it->get_coord)){
                top5.push_back(*it);
            }
        }
        
    }
    return top5;
}

 double calculerDistance(GPS coord1, GPS coord2) {
    double deltaX = coord2.get_latitude() - coord1.get_latitude();
    double deltaY = coord2.get_longitude() - coord1.get_longitude();
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
    return distance;
}


vector<Measurement> get_measures_of_sensor(string sensorId,  Date start, Date end){
    vector<Measurement> result;
    Sensor sensor = getSensorById(sensorId);
    vector<Measurement>::iterator itDebut = sensor.get_measurements().begin();
    vector<Measurement>::iterator itFin = sensor.get_measurements().end();
    for (auto it = itDebut; it != itFin; ++it) {
        if(it->get_timestamp < end && it->get_timestamp>start){
            result.push_back(*it);
        }
    }
    return result;
}

Sensor getSensorById(string sensorId){
    vector<Sensor>::iterator itDebut = sensors.begin();
    vector<Sensor>::iterator itFin = sensors.end();
    bool fin =false;
    while (itDebut != itFin && !fin) {
        if (itDebut->get_id() == sensorId) {
            return *itDebut;
        }
        ++itDebut;
    }
    return Sensor();
}



