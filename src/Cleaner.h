#if !defined(CLEANER_H)
#define CLEANER_H

#include "Date.h"
#include "Device.h"
#include <vector>

class Cleaner : public Device {
protected:
    Date timestamp_start;
    Date timestamp_stop;

public:
    std::vector<std::string> get_impact();
    Cleaner(const std::string &id);
    Cleaner() {}
    void set_timestamp_start(Date date);
    void set_timestamp_stop(Date date);
    Date get_timestamp_start() const;
    Date get_timestamp_stop() const;
};
#endif
