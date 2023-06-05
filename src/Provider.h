#include <unordered_map>
#if !defined(PROVIDER_H)
#define PROVIDER_H

#include "Cleaner.h"
#include <string>
#include <vector>

class Provider {
protected:
    std::string id;
    std::unordered_map<std::string, Cleaner *> cleaners;

public:
    Provider();
    Provider(const std::string &id);
    void add_cleaner(Cleaner &cleaner);
    friend bool operator<(const Provider &unProvider,
                          const Provider &autreProvider);
    std::string get_id() const { return id; }
    std::unordered_map<std::string, Cleaner *> get_cleaners() const {
        return cleaners;
    }
};
bool operator<(const Provider &unProvider, const Provider &autreProvider);
#endif
