#if !defined(PERSON_H)
#define PERSON_H

#include "Date.h"
#include "GPS.h"
#include "Measurement.h"
#include "Sensor.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Person {
public:
    bool Log_in(const std::string &login, const std::string &password);

    bool Log_in_2fa(const std::string &login, const std::string &password);

    void Log_out();

    // virtual bool Sign_up(std::string login, std::string password) = 0;

    std::vector<double> Stats_circular_area(const GPS &position,
                                            const double &radius,
                                            const Date &start, const Date &end);

    std::vector<double> Stats_precise_position(const GPS &position,
                                               const Date &start,
                                               const Date &end, Date &proche);

protected:
    Person();

    Person(std::string login, std::string password);

    std::string login;

    std::string password;
};
#endif
