#if ! defined ( PERSON_H )
#define PERSON_H

#include <vector>
#include <string>


class Person{
public:
  bool Log_in(std::string login, std::string password);

  bool Log_in_2fa(std::string login, std::string password);

  void Log_out();

  virtual bool Sign_up(std::string login, std::string password);
  
  std::vector<int> Stats_circular_area(GPS position, double radius, Date start, Date end);

  std::vector<int> Stats_precise_position(GPS position, Date start, Date end);

protected:
  std::string login;
  
  std::string password;
};
#endif
