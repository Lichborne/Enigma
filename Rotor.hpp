#ifndef ROTOR_H
#define ROTOR_H

#include"Constants.hpp"
#include"IO.hpp"


// Class to represent Rotor.
class Rotor {
private:

    // It is possible to do the exercise without this -> but it is much simpler
    // this way.
    std::vector<int> Absolute_Positions = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
                                           15,16,17,18,19,20,21,22,23,24,25};

    // Vector to hold momentary positions. Vector because erase and
    // push_back methods make rotation simpler.
    std::vector<int> Relative_Positions = {};

    // Vector to hold notch positions.There can be any number of them->vector.
    std::vector<int> Notch_Positions = {};


public:
    // Default Constructor
    Rotor();

    // Constructor
    Rotor(char* filename, int starting_position);

    // Rotate rotor once
    void Rotate();

    // Tells us if, depending on th notch position in the current rotor,
    // the next one should be rotated.
    bool Rotate_Next_Rotor();

    // Put an input through a rotor forwards
    int Transform(int input);

    // Put an input through a rotor backwards 
    int Backtrack(int input);

};

#endif

