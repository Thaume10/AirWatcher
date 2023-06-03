#if !defined(DATE_H)
#define DATE_H

#include <ctime>
#include <string>

class Date {
protected:
    std::time_t time;

public:
    Date();
    std::string To_string();
    void String_to_time(std::string time);

    bool operator<(const Date &other) const { return time < other.time; }

    // Surcharge de l'opérateur supérieur strict (>)
    bool operator>(const Date &other) const { return time > other.time; }

    Date operator-(const Date &other) const {
        Date result;
        result.time = this->time - other.time;
        return result;
    }

    void add_days(int d);
};
#endif
