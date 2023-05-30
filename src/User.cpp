#include "User.h"

#include "Data.h"

using namespace std;

User::User(){

}

User::User(string id, int points, bool is_trustworthy) : id(id), points(points), is_trustworthy(is_trustworthy) {
}

// bool User::Sign_up(std::string login, std::string password) {
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

void User::add_sensor(Sensor sensor) {
    sensors.push_back(sensor);
}

std::string User::getId()const{
  return id;
}

std::vector<Sensor> User::getSensors()const{
  return sensors;
}

bool operator < (const User & unUser, const User & autreUser){
  return (unUser.getId() < autreUser.getId());
}
