#if !defined(ATTRIBUTE_H)
#define ATTRIBUTE_H

#include <string>

class Attribute {
public:

 std::string get_id() const {
        return id;
    }

 void set_id(std::string id) {
     this->id = id;
 }

protected:
    std::string id;
    std::string unit;
    std::string description;
};
#endif
