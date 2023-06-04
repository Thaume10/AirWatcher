#include "User.h"

#include "Data.h"
#include <unordered_map>

using namespace std;

User::User() {}

User::User(const string &id, int points, bool is_trustworthy)
    : id(id), points(points), is_trustworthy(is_trustworthy) {}

// bool User::sign_up(string login, string password) {
//     this->login = login;
//     this->password = password;
//     // TODO: vérifier unique

//     bool is_unique = true;

//     for (const auto &user : Data.users) {
//         if (user.id == login) {
//             is_unique = false;
//         }
//     }

//     return is_unique;
// }

void User::add_sensor(Sensor &sensor) { sensors[sensor.get_id()] = &sensor; }

string User::get_id() const { return id; }

unordered_map<string, Sensor*> User::get_sensors() const { return sensors; }

bool operator<(const User &unUser, const User &autreUser) {
    return (unUser.get_id() < autreUser.get_id());
}
