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
    Cleaner(std::string id);
    void set_timestamp_start(Date date);
    void set_timestamp_stop(Date date);
};
#endif
