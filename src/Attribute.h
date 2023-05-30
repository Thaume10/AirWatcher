#if !defined(ATTRIBUTE_H)
#define ATTRIBUTE_H

#include <string>

class Attribute {
public:

inline std::string get_id() const {
        return id;
    }

protected:
    std::string id;
    std::string unit;
    std::string description;
};
#endif
