#if !defined(DATE_H)
#define DATE_H

#include <string>
#include <ctime>

class Date {
protected:
    std::time_t time;

public:
    Date();
    std::string Time_to_string();
    std::time_t String_to_time(std::string time);
};
#endif
