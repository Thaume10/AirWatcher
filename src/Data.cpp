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

