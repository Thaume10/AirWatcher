#if !defined(DEVICE_H)
#define DEVICE_H

#include <string>
#include "GPS.h"

class Device {
  public:
    inline GPS get_coord() const {
        return coord;
    }
    inline std::string get_id() const {
        return id;
    }

  protected:
    std::string id;
    GPS coord;

};
#endif
