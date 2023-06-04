#if !defined(DEVICE_H)
#define DEVICE_H

#include "GPS.h"
#include <string>

class Device {
public:
    Device();

    GPS get_coord() const { return coord; }
    std::string get_id() const { return id; }
    void set_coord(GPS pos) { coord = pos; }

protected:
    std::string id;
    GPS coord;
};
#endif
