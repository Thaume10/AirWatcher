#include <iostream>
#include "Data.h"
using namespace std;

int main(){
  Data::Load_CSV();

  vector<User> users = Data::getUsers();
  for(vector<User>::iterator itUsers = users.begin(); itUsers!=users.end(); ++itUsers){
    cout << "User : " << itUsers->getId() << endl;
    std::vector<Sensor> sensors = itUsers->getSensors();
    for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor != sensors.end(); ++itSensor){
      cout << "\tSensor : " << itSensor->get_id() << " coordonnees : " << itSensor->get_coord().get_latitude() << " : " << itSensor->get_coord().get_longitude() << endl;
    }
  }

  vector<Sensor> sensors = Data::getSensors();
  for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor!= sensors.end(); ++itSensor){
    cout << "Sensor : " << itSensor->get_id() << " coordonnees : " << itSensor->get_coord().get_latitude() << " " << itSensor->get_coord().get_longitude() << endl;
  }

  return 0;
}
