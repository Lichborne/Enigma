#include"Statically_Connected_Components.hpp"
#include"IO.hpp"

//===========================================================================

// See comments in main.cpp for why this is good to have
Statically_Connected_Components::Statically_Connected_Components() {}

//===========================================================================

Statically_Connected_Components::Statically_Connected_Components(char* filename) {
    
    // 
    std::vector<int> settings = Enigma_IO::read_settings(filename);
    
    //elem is unsigned int because of .size()
    for (unsigned int elem = 0; elem < settings.size(); elem += 2) {
        
        All_Cables.push_back(Cable(settings[elem], settings[elem+1]));
    }
}

//===========================================================================

int Statically_Connected_Components::Switch_Up_Single(int input) {
    int switched;
    for (unsigned int c = 0; c < All_Cables.size(); c++) {
        if (All_Cables[c].Cable_connected(input)) {
            switched = All_Cables[c].Cable_swap(input);
            return switched;
        }
    }
    return input;
}

//===========================================================================

// See comments in main.cpp for why this is good to have
Plugboard::Plugboard() {}

Plugboard::Plugboard(char* filename):
                            Statically_Connected_Components(filename) {}

//===========================================================================

// See comments in main.cpp for why this is good to have
Reflector::Reflector() {}

Reflector::Reflector(char* filename):
                            Statically_Connected_Components(filename) {}

//===========================================================================