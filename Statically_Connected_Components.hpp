#ifndef STATICALLY_CONNECTED_COMPONENTS_H
#define STATICALLY_CONNECTED_COMPONENTS_H
#include"Cable.hpp"
#include<vector>

// Class to represent components whose wiring or cabelling remains the same
// throughout a single encryption/decription cycle, and who map letters in
// pairs, i.e., here, the plugboard and reflector. In my implementation, these
// two components are only differentiated by the length of the vectors of which
// they are comprised. Because of this, I avoided a lot of duplicate code by
// having this base class, and having plugboard and reflector be derived
// classes. The class and the derived classes are in a single pair of hpp and 
// cpp because the files for plugboard and reflector separately were about 5 
// lines each so I believe this is much more conveniently laid out in one pair
// of hpp and cpp files.

class Statically_Connected_Components {

private:
    // Vector attribute to contain the arbitrary number of cables or wires
    // in a given statycally connected component configuration.
    // Not necessary, could be done via modulo operation, but it is
    // a good representation of the real world, and can potentially
    // be reused. 
    std::vector<Cable> All_Cables = {};

public:
    // Default Constructor
    Statically_Connected_Components();

    // Constructor
    Statically_Connected_Components(char* filename);

    // Puts an input through the cables of a statically connected component
    int Switch_Up_Single(int input);
}; 

// Plugboard class is a child of statically connected components
class Plugboard: public Statically_Connected_Components {
public:
    // Default Constructor
    Plugboard();

    // Constructor
    Plugboard(char* filename);
};

// Reflector class is a child of statically connected components
class Reflector: public Statically_Connected_Components {
public:
    // Default Constructor
    Reflector();

    // Constructor
    Reflector(char* filename);
};

#endif