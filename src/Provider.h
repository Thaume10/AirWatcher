#if !defined(PROVIDER_H)
#define PROVIDER_H

#include "Cleaner.h"
#include <string>
#include <vector>

class Provider {
protected:
    std::string id;
    std::vector<Cleaner> cleaners;

public:
    Provider();
    Provider(const std::string &id);
    void add_cleaner(const Cleaner &cleaner);
    friend bool operator<(const Provider &unProvider,
                          const Provider &autreProvider);
    std::string get_id() const { return id; }
    std::vector<Cleaner> get_cleaners() { return cleaners; }
};
bool operator<(const Provider &unProvider, const Provider &autreProvider);
#endif
