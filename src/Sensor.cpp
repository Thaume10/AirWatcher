#include "Sensor.h"

using namespace std;

Sensor::Sensor(string id) {
    this->id = id;
}

Sensor::Sensor(string id, bool is_malfunctionning) : is_malfunctionning(is_malfunctionning) {
    this->id = id;
}
