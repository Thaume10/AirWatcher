#include <iostream>
#include "Data.h"
#include "User.h"
using namespace std;

void unitTestsPrecisePosition(){
    User u;
    Date start;
    Date end;
    start.String_to_time("2023-01-01 10:00:00");
    end.String_to_time("2023-01-01  14:00:00");
    cout<<endl<<endl;
    cout<<"Unit test valide avec sensors créés :"<<endl;
    vector<double> valid = u.Stats_precise_position(GPS(0.5,0.5) ,start ,end ) ;
    cout<<"------------------------"<<endl;
    std::cout<<"O3\tSO2\tNO2\tPM10"<<endl;
    for (double value : valid) {
        std::cout << value << "\t";
    }
    std::cout << std::endl;


    start.String_to_time("2019-01-09 10:00:00");
    end.String_to_time("2019-01-09  14:00:00");
    cout<<endl<<endl;
    cout<<"Unit test valide avec jeux de donée :"<<endl;
    vector<double> valid2 = u.Stats_precise_position(GPS(44.2,2.4) ,start ,end ) ;
    cout<<"------------------------"<<endl;
    std::cout<<"O3\tSO2\tNO2\tPM10"<<endl;
    for (double value : valid2) {
        std::cout << value << "\t";
    }
    std::cout << std::endl;

    start.String_to_time("2019-01-09 14:00:00");
    end.String_to_time("2019-01-09  10:00:00");
    cout<<endl<<endl;
    cout<<"Unit test invalide  :"<<endl;
    vector<double> valid3 = u.Stats_precise_position(GPS(44.2,2.4) ,start ,end ) ;
    if(valid3.empty()){
      cout<<"L'heure de fin est plus petite que l'heure de début"<<endl;
    }

}

int main(){
  Data::Load_CSV();

  cout << "----------------USERS--------------" << endl;
  vector<User> users = Data::getUsers();
  for(vector<User>::iterator itUsers = users.begin(); itUsers!=users.end(); ++itUsers){
    cout << "User : " << itUsers->getId() << endl;
    std::vector<Sensor> sensors = itUsers->getSensors();
    for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor != sensors.end(); ++itSensor){
      //cout << "\tSensor : " << itSensor->get_id() << " coordonnees : " << itSensor->get_coord().get_latitude() << " : " << itSensor->get_coord().get_longitude() << endl;
    }
  }

  cout << "----------------SENSORS--------------" << endl;
  vector<Sensor> sensors = Data::getSensors();
  for(vector<Sensor>::iterator itSensor = sensors.begin(); itSensor!= sensors.end(); ++itSensor){
    //cout << "Sensor : " << itSensor->get_id() << " coordonnees : " << itSensor->get_coord().get_latitude() << " " << itSensor->get_coord().get_longitude() << endl;
  }

  cout << "----------------CLEANERS--------------" << endl;
  vector<Cleaner> cleaners = Data::getCleaners();
  for(vector<Cleaner>::iterator itCleaners = cleaners.begin(); itCleaners !=cleaners.end(); ++itCleaners){
   // cout << "Cleaner : " << itCleaners->get_id() << " coord : " << itCleaners->get_coord().get_latitude() << " : " << itCleaners->get_coord().get_longitude() << " Debut : " << itCleaners->get_timestamp_start().To_string() <<  " Fin : " << itCleaners->get_timestamp_stop().To_string() << endl;
  }

  cout << "----------------MEASUREMENTS--------------" << endl;
  vector<Measurement> measurements = Data::getMeasurements();
  for(vector<Measurement>::iterator itMeasurements = measurements.begin(); itMeasurements !=measurements.end(); ++itMeasurements){
    //cout << "Measurement value : " << itMeasurements->get_value() << " timestamp : " << itMeasurements->get_timestamp().To_string() << " attribute : " << itMeasurements->get_attribute().get_id() << endl;
  }
  unitTestsPrecisePosition();

  cout << "----------------PROVIDERS--------------" << endl;
  vector<Provider> providers = Data::getProviders();
  for(vector<Provider>::iterator itProvider = providers.begin(); itProvider !=providers.end(); ++itProvider){
    cout << "Provider id : " << itProvider->get_id() << endl;
    vector<Cleaner> cleaners = itProvider->get_cleaners();
    for(vector<Cleaner>::iterator itCleaner = cleaners.begin(); itCleaner != cleaners.end(); ++itCleaner){
      cout << "Cleaner : " << itCleaner->get_id() << " coord : " << itCleaner->get_coord().get_latitude() << " : " << itCleaner->get_coord().get_longitude() << " Debut : " << itCleaner->get_timestamp_start().To_string() <<  " Fin : " << itCleaner->get_timestamp_stop().To_string() << endl;
    }
  }

  return 0;
}

