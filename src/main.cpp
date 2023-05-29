#include <iostream>
#include "Data.h"
using namespace std;

int main(){
  Data data;
  data.Load_CSV();

  vector<User> users = data.getUsers();
  for(vector<User>::iterator itUsers = users.begin(); itUsers!=users.end(); ++itUsers){
    cout << "User : " << itUsers->getId() << endl;
    std::vector<Sensor> sensors = itUsers->getSensors();
    for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor != sensors.end(); ++itSensor){
      cout << "\tSensor : " << itSensor->id << endl;
    }
  }

  return 0;
}
