#include "creature_tracker.h"

//constructor initializes the class
CreatureTracker::CreatureTracker() : 
    tree_creatures(), //for binrary search tree
    ht_stats(101) {} //for hash table with 101 capacity

//destructor to free all associated memory
CreatureTracker::~CreatureTracker() {
    clear(); //calls the clear function
}

//adds a new creature and both tree and hash table are updated
void CreatureTracker::add_creature(const std::string& name, const std::string& type, int power) {
    Creature new_creature(name, type, power); //creates a new creature
    tree_creatures.insert(new_creature); //adds the new creature into the binary search tree
    
    CreatureTypeStats* stats = ht_stats.get(type); //gets the stats for the given type from hash table
    if (stats == nullptr) { //checks if stats is nullptr so does not exist
        CreatureTypeStats new_stats(type); //creates a new creaturetypestats object
        new_stats.increment_count(); //increments the creature count
        new_stats.add_power(power); //adds the new creature power
        ht_stats.insert(new_stats); //inserts the new stats object in hash table

    } else {
        stats->increment_count(); //updates the stats object by incrementing the count
        stats->add_power(power); //updates stats object with the new creatures power
    }
}

//removes a creature and both tree and hash table are updated
void CreatureTracker::remove_creature(const std::string& name) {
    Creature* creature = tree_creatures.find(name); //finds the creatue in the binary search tree
    if (creature != nullptr) { //checks if the creature is not nullptr so exists
        std::string type = creature->get_type(); //gets the type of the creature
        int power = creature->get_power(); //gets the power 
        tree_creatures.remove(name); //removes the creature from the binary search tree

        CreatureTypeStats* stats = ht_stats.get(type); //gets the stats for the given type from hash table
        if (stats != nullptr) { //checks if the stats is not nullptr so exists
            stats->decrement_count(); //updates the stat object by decrementing the count
            stats->subtract_power(power); //updates the stats object by removing the power

            if (stats->get_count() == 0) { //checks if no creatures of this type exists
                ht_stats.remove(type); //removes the stats from hash table
            }
        }
    }
}

//checks if a creature with the supplied name exists
bool CreatureTracker::creature_exists(const std::string& name) {
    return tree_creatures.find(name) != nullptr; //returns true if the creature exists in the binary search tree
}

//gets a pointer to the Creature with the supplied name, or nullptr if it does not exist
Creature* CreatureTracker::get_creature(const std::string& name) {
    return tree_creatures.find(name); //returns a pointer to the creature if it exists or returns a nullptr
}

//returns a count of the number of creatures with the supplied type
int CreatureTracker::type_count(const std::string& type) {
    CreatureTypeStats* stats = ht_stats.get(type); //gets the stats ibject for the givemn type from hash table
    if (stats != nullptr) { //checks if stats is not nullptr so exists
        return stats->get_count(); //returns the count of creatures of the mentioned type
    }
    else {
        return 0; //returns 0 if it doesnt exist
    } 
}

// Return the total power of the creatures with the supplied type
int CreatureTracker::type_power(const std::string& type) {
    CreatureTypeStats* stats = ht_stats.get(type); //gets the stats for the given type from hash table
    if (stats != nullptr) { //checks if stats is not nullptr so exists
        return stats->get_total_power(); //returns the total power of creatures of the mentioned type
    }
    else {
        return 0; //returns 0 if it doesnt exist
    }
}

//gets a pointer to the CreatureTypeStats with the supplied type, or nullptr if it does not exist
CreatureTypeStats* CreatureTracker::get_stats(const std::string& type) {
    return ht_stats.get(type); //returns a pointer to the stats object if it exists 
}

//clears all nodes from tree, entries from hash table and associated memory is reclaimed
void CreatureTracker::clear() {
    tree_creatures.clear(); //clears all nodes from binary search tree
    ht_stats.clear(); //clears all entries from hash table
}

//appends both the creature tree and the type stats hash table to the stream
void CreatureTracker::print(std::ostream& os) const {
    os << "Creatures: " << tree_creatures << std::endl; //appends the binary search tree
    os << "Type stats: " << std::endl; //appends for the type stats
    ht_stats.print(os); //appends the hash table
}

// appends both the creature tree and the type stats hash table to the stream using the print function
std::ostream& operator<<(std::ostream& out, const CreatureTracker& tracker) {
    tracker.print(out); //uses print method to append creature tracker
    return out; //returns the output stream
}
