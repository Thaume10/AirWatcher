#if !defined(ADMIN_H)
#define ADMIN_H

#include "Person.h"
#include <vector>

class Admin : public Person {
public:
    Admin(std::string login, std::string password);

    std::vector<std::string> get_logs(std::string user_id);

    void manage_settings();

protected:
};
#endif
