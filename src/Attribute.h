#if !defined(ATTRIBUTE_H)
#define ATTRIBUTE_H

#include <string>

class Attribute {
public:
    Attribute() {}
    Attribute(std::string id, std::string unit, std::string description)
        : id(id), unit(unit), description(description) {}
    std::string get_id() const { return id; }

    void set_id(const std::string &id) { this->id = id; }

protected:
    std::string id;
    std::string unit;
    std::string description;
};
#endif
