#if !defined(GOVERNMENTMEMBER_H)
#define GOVERNMENTMEMBER_H

#include "Person.h"

class GovernmentMember : public Person {
public:
    bool analyze_sensor(std::string sensor_id);
    bool mark_user_data_as_false(std::string user_id);
    bool mark_sensor_data_as_false(std::string sensor_id);
};
#endif
