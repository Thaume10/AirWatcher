#if !defined(CLEANER_H)
#define CLEANER_H 

#include <vector>
#include "Date.h"
#include "Device.h"

class Cleaner : public Device {
protected:
    Date timestamp_start;
    Date timestamp_stop;

public:
    std::vector<std::string> get_impact();
};
#endif
