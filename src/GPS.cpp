#include "GPS.h"

GPS::GPS() {
    latitude = 0;
    longitude = 0;
}

GPS::GPS(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}
