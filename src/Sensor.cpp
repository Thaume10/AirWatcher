#include "Sensor.h"

using namespace std;

Sensor::Sensor(){

}

Sensor::Sensor(string id) {
    this->id = id;
}

Sensor::Sensor(string id, bool is_malfunctionning) : is_malfunctionning(is_malfunctionning) {
    this->id = id;
}

bool operator < (const Sensor & unSensor, const Sensor & autreSensor){
  return unSensor.get_id() < autreSensor.get_id();
}
