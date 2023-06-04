#if !defined(USER_H)
#define USER_H

#include "Person.h"
#include "Sensor.h"
#include <string>
#include <vector>

class User : public Person {
public:
    User();

    User(const std::string &id, int points = 0, bool is_trustworthy = true);

    User(const std::string &login, const std::string &password,
         const std::string &id, int points = 0, bool is_trustworthy = true);

    void add_sensor(const Sensor &sensor);

    // virtual bool sign_up(std::string login, std::string password);

    std::string get_id() const;

    std::vector<Sensor> get_sensors() const;

    friend bool operator<(const User &unUser, const User &autreUser);

protected:
    std::string id;
    int points;
    bool is_trustworthy;
    std::vector<Sensor> sensors;
};

bool operator<(const User &unUser, const User &autreUser);

#endif
