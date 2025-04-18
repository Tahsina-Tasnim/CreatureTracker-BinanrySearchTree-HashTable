#include "creature_type_stats.h"

//constructor initializes a new CreatureTypeStats with an empty type, count 0, and total power 0
CreatureTypeStats::CreatureTypeStats() : 
    type(""), 
    count(0), 
    total_power(0) {}

//second constructor initializes a new CreatureTypeStats with the specified type, count 0, and total_power 0
CreatureTypeStats::CreatureTypeStats(const std::string& type) : 
    type(type), 
    count(0), 
    total_power(0) {}

//empty destructor as no dynamic memory is allocated 
CreatureTypeStats::~CreatureTypeStats() {}

//returns a reference to the type of the CreatureTypeStats
const std::string& CreatureTypeStats::get_key() const {
    return type;
}

//returns the count of creatures of this type
int CreatureTypeStats::get_count() const {
    return count;
}

//returns the total power of creatures of this type
int CreatureTypeStats::get_total_power() const {
    return total_power;
}

//increments the count of creatures of this type by 1
void CreatureTypeStats::increment_count() {
    ++count;
}

//decrements the count of creatures of this type by 1
void CreatureTypeStats::decrement_count() {
    --count;
}

//adds the supplied amount to the total power of creatures of this type
void CreatureTypeStats::add_power(int amount) {
    total_power += amount;
}

//subtracts the supplied amount from the total power of creatures of this type
void CreatureTypeStats::subtract_power(int amount) {
    total_power -= amount;
}

//appends the CreatureTypeStats details to the stream
std::ostream& operator << (std::ostream& os, const CreatureTypeStats& c) {
    os << "(" << c.get_key() << ", " << c.get_count() << ", " << c.get_total_power() << ")";
    return os;
}

//checks if two CreatureTypeStats objects have the same type
bool operator == (const CreatureTypeStats& c1, const CreatureTypeStats& c2) {
    return c1.get_key() == c2.get_key();
}

//checks if the type of the first CreatureTypeStats object is alphabetically before the type of the second CreatureTypeStats object
bool operator < (const CreatureTypeStats& c1, const CreatureTypeStats& c2) {
    return c1.get_key() < c2.get_key();
}

//checks if the type of the first CreatureTypeStats object is alphabetically after the type of the second CreatureTypeStats object
bool operator > (const CreatureTypeStats& c1, const CreatureTypeStats& c2) {
    return c1.get_key() > c2.get_key();
}
