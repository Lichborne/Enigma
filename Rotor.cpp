#include<vector>
#include<algorithm>
#include"Rotor.hpp"


//===========================================================================

// See comments in main.cpp for why this is good to have
Rotor::Rotor() {}

//===========================================================================

Rotor::Rotor(char* filename, int starting_position) {

    std::vector<int> settings = Enigma_IO::read_settings(filename);

    for (int i = 0; i < ALPHABET_SIZE; i++) {

        Relative_Positions.push_back(settings[i] - i);
    }
    // i is unsigned int because of .size()
    for (unsigned int i = ALPHABET_SIZE; i < settings.size(); i++) {
        Notch_Positions.push_back(settings[i]);
    }
    // set starting position
    for (int i = 0; i < starting_position; i++) {
        Rotate();
    }
}

//===========================================================================

void Rotor::Rotate() {

    std::rotate(Relative_Positions.begin(),Relative_Positions.begin()+1,Relative_Positions.end());
    std::rotate(Absolute_Positions.begin(),Absolute_Positions.begin()+1,Absolute_Positions.end());
}

//===========================================================================

bool Rotor::Rotate_Next_Rotor() {

    if (std::find(Notch_Positions.begin(), Notch_Positions.end(), 
                    Absolute_Positions[0]) != Notch_Positions.end())
        return true;
    return false;
}

//===========================================================================


int Rotor::Transform(int input) {

    int transformed;
    transformed = (ALPHABET_SIZE + ((input + (Relative_Positions[input])) 
                                       % ALPHABET_SIZE)) % ALPHABET_SIZE;
    return transformed;
}  

//===========================================================================

int Rotor::Backtrack(int input) {

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((ALPHABET_SIZE + ((i + (Relative_Positions[i])) % ALPHABET_SIZE)) 
                                                    % ALPHABET_SIZE == input)
            return i;
    }
    // flow of control will never get here, but compiler is crying:
    exit(1);
}

//===========================================================================
