#if !defined(DEVICE_H)
#define DEVICE_H

#include <string>
#include "GPS.h"

class Device {
public:
    std::string id;
    GPS coord;
};
#endif
