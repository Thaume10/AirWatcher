#if ! defined ( PERSON_H )
#define PERSON_H

#include <vector>
#include <string>
#include <utility> 
#include <iostream>
#include "Date.h"
#include "Data.h"
#include "GPS.h"
#include "Sensor.h"
#include "Measurement.h"

using namespace std;

class Person{
public:
  
  bool Log_in(std::string login, std::string password);

  bool Log_in_2fa(std::string login, std::string password);

  void Log_out();

  virtual bool Sign_up(std::string login, std::string password) = 0;
  
  std::vector<double> Stats_circular_area(GPS position, double radius, Date start, Date end);

  std::vector<double> Stats_precise_position(GPS position, Date start, Date end);

protected:
  Person();

  Person(std::string login, std::string password);

  std::string login;
  
  std::string password;
};
#endif
