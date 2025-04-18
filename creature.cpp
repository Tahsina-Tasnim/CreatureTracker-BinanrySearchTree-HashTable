#include "creature.h"

//constructor initializes name, type and power of 0
Creature::Creature() : 

      name(""), 
      type(""), 
      power(0) {}

// second constructor nitializes a new creature with the specified name, type, and power
Creature::Creature(const std::string& name, const std::string& type, int power) :
      name(name), 
      type(type), 
      power(power) {}

//empty destructor as no dynamic memory
Creature::~Creature() {

}

//returns a reference to the name of the creature
const std::string& Creature::get_key() const {
    return name;
}

//returns a reference to the type of the creature
const std::string& Creature::get_type() const {
    return type;
}

//returns the power rating of the creature
int Creature::get_power() const {
    return power;
}

//appends the creatures details to the stream
std::ostream& operator << (std::ostream& os, const Creature& c) {
    os << "(" << c.get_key() << ", " << c.get_type() << ", " << c.get_power() << ")";
    return os;
}

//checks if two creatures have the same name
bool operator == (const Creature& c1, const Creature& c2) {
    return c1.get_key() == c2.get_key();
}

//checks if the first creature name is alphabetically before the second creatures name
bool operator < (const Creature& c1, const Creature& c2) {
    return c1.get_key() < c2.get_key();
}

//checks if the first creatures name is alphabetically after the second creatures name
bool operator > (const Creature& c1, const Creature& c2) {
    return c1.get_key() > c2.get_key();
}
