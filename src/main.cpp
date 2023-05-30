#include <iostream>
#include "Data.h"
#include "Person.h"
using namespace std;

void unitTestsPrecisePosition(){
    person p;
    Date start;
    Date end;
    start.String_to_time("07/07/2019  12:00:00");
    end.String_to_time("20/11/2019  12:00:00")
    vector<double> valid = p.Stats_precise_position(GPS(43,2) ,start ,end ) ;
    std::cout<<"O3\tSO2\tNO2\tPM10"
    for (double value : valid) {
        std::cout << value << "\t";
    }
    std::cout << std::endl;

}

int main(){
  Data::Load_CSV();

  cout << "----------------USERS--------------" << endl;
  vector<User> users = Data::getUsers();
  for(vector<User>::iterator itUsers = users.begin(); itUsers!=users.end(); ++itUsers){
    cout << "User : " << itUsers->getId() << endl;
    std::vector<Sensor> sensors = itUsers->getSensors();
    for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor != sensors.end(); ++itSensor){
      cout << "\tSensor : " << itSensor->get_id() << " coordonnees : " << itSensor->get_coord().get_latitude() << " : " << itSensor->get_coord().get_longitude() << endl;
    }
  }

  cout << "----------------SENSORS--------------" << endl;
  vector<Sensor> sensors = Data::getSensors();
  for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor!= sensors.end(); ++itSensor){
    cout << "Sensor : " << itSensor->get_id() << " coordonnees : " << itSensor->get_coord().get_latitude() << " " << itSensor->get_coord().get_longitude() << endl;
  }

  cout << "----------------CLEANERS--------------" << endl;
  vector<Cleaner> cleaners = Data::getCleaners();
  for(vector<Cleaner>::iterator itCleaners = cleaners.begin(); itCleaners !=cleaners.end(); ++itCleaners){
    cout << "Cleaner : " << itCleaners->get_id() << " coord : " << itCleaners->get_coord().get_latitude() << " : " << itCleaners->get_coord().get_longitude() << " Debut : " << itCleaners->get_timestamp_start().To_string() <<  " Fin : " << itCleaners->get_timestamp_stop().To_string() << endl;
  }
  return 0;
}

