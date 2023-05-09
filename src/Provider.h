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
    Provider(std::string id);
};
#endif
