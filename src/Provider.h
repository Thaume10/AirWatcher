#if !defined(PROVIDER_H)
#define PROVIDER_H

#include <vector>
#include <string>
#include "Cleaner.h"

class Provider {
protected:
    std::string id;
    std::vector<Cleaner> cleaners;

public:
    Provider();
    Provider(std::string id);
    void add_cleaner(Cleaner cleaner);
    std::string get_id()const{
      return id;
    }
    std::vector<Cleaner> get_cleaners(){
      return cleaners;
    }
};
bool operator < (const Provider & unProvider, const Provider & autreProvider);
#endif
