#include "User.h"

using namespace std;

User::User(string id, int points, bool is_trustworthy) : id(id), points(points), is_trustworthy(is_trustworthy) {
}

bool User::Sign_up(std::string login, std::string password) {
    this->login = login;
    this->password = password;
    // TODO: vérifier unique
    return true;
}

void User::add_sensor(Sensor sensor) {
    sensors.push_back(sensor);
}
