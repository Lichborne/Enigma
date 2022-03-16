#ifndef ENIGMA_H
#define ENIGMA_H

#include"Statically_Connected_Components.hpp"
#include"Rotor.hpp"
#include"IO.hpp"
#include"Constants.hpp"

// To encapsulate a particular Enigma machine

class Enigma {
private:
    // Recorded because it is used multiple times
    int Rotor_Chain_Size = 0;

    // The Plugboard and Reflector for the machine
    Plugboard Enigma_Plugboard = Plugboard();

    Reflector Enigma_Reflector = Reflector();

    // All the rotors, connected into one chain
    std::vector<Rotor> Rotor_Chain = {};

    // run an encrypt (or decrypt) sequence on an input
    int Encrypt_Decrypt_Cycle(int input);

    // Rotate next rotor under certain conditions
    void Rotate_Next_Maybe(int index);   

public:
    // Default Constructor
    Enigma();

    // Constructor
    Enigma(int argc, char **argv);

    // To use a constructed machine.
    void Use_Machine();

    // Notice that there are no getters and setters. That is because none
    // are needed; once an enigma is set up, in can be used, and if you
    // want to use a different initial setup, you have to set up the 
    // entire machine again. Absolutely no messing with the internal state,
    // the components update themselves automatically.
};

#endif



