#if ! defined ( USER_H )
#define USER_H

#include <vector>
#include <string>
#include "Sensor.h"
#include "Person.h"

class User : public Person{
public:
  User();

  User(std::string id, int points = 0, bool is_trustworthy = true);

  User(std::string login, std::string password, std::string id, int points = 0, bool is_trustworthy = true);

  void add_sensor(Sensor sensor);
  virtual bool Sign_up(std::string login, std::string password);

protected:
  std::string id;
  int points;
  bool is_trustworthy;
  std::vector<Sensor> sensors;
};
#endif
