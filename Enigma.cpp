#include<algorithm>
#include<vector>
#include<iostream>
#include"Enigma.hpp"

//===========================================================================

// See comments in main.cpp for why this is good to have
Enigma::Enigma() {}
   
//===========================================================================

// Some members could be initialized with :, but cleaner this way,
// because we have some checks to do first! Could do in main, but
// it's better to obscure this because it isn't very elegant due to
// the way errors are handled.
Enigma::Enigma(int argc, char **argv) {

    // Before we do anything, check if there are enough parameters.
    Enigma_IO::check_parameter_number(argc);

    // Check if the oprder of files is correct.
    Enigma_IO::check_file_order(argc, argv);
    
    // The position file is the last one:
    int position_file_i = argc - 1;
        
    // Clever bit to determine the number of rotors based on number of args.
    // Faster than using filetype (remember, correct file order was already 
    // checked! See starred comment *1 at the bottom of file.
    if (argc > 3) {
        Rotor_Chain_Size = argc - 4;
    } else {
        Rotor_Chain_Size = 0;
    }
    
    // Configure Plugboard
    Enigma_Plugboard = Plugboard(argv[1]);

    // Configure Reflector
    Enigma_Reflector = Reflector(argv[2]);
    
    // Configure Rotors

    // *2: minor, but long detail, comment at bottom of file to not distract. 
    std::vector<int> rotor_positions = 
                Enigma_IO::read_rotor_positions(argv[position_file_i], 
                                                    Rotor_Chain_Size);

    // Place rotors in Rotor_Chain in REVERSE ORDER to how they are given.
    for (int i = Rotor_Chain_Size - 1; i >= 0 ; i--) {
        Rotor_Chain.push_back(Rotor(argv[i+3], rotor_positions[i]));
    }
}

//===========================================================================

// Encrypt (or Decrypt) Cycle.
int Enigma::Encrypt_Decrypt_Cycle(int input) {

    //Send input through plugboard
    input = Enigma_Plugboard.Switch_Up_Single(input);

    // Send a letter through rotors one way, after rotation(s) 
    // where necessary. Rotors already reversed in order on input
    // so we go upwards here. See starred comment *3 on order of rotations.
    for (int rotor_i = 0; rotor_i < Rotor_Chain_Size; rotor_i++) {
        
        if (rotor_i == 0)
            Rotor_Chain[rotor_i].Rotate();
        
        Rotate_Next_Maybe(rotor_i);
        
        input = Rotor_Chain[rotor_i].Transform(input);
    }

    // Send a letter through reflector
    input = Enigma_Reflector.Switch_Up_Single(input);

    // Send a letter through rotors in reverse
    for (int rotor_i = Rotor_Chain_Size-1; rotor_i >= 0; rotor_i--) {
        input = Rotor_Chain[rotor_i].Backtrack(input);
    }

    // Send letter through plugboard again (plugboard has paired cables,
    // so back and forth is the same.
    input = Enigma_Plugboard.Switch_Up_Single(input);

    return input;
}

//===========================================================================

// Since the conditions of exit are dependent on input, this is eadier in
// a single function, which is why it is not in Enigma_IO.
void Enigma::Use_Machine() {

    char c;
    int encrypted;

    while ((std::cin >> c).good()) {

        Enigma_IO::check_console_input(c);

        encrypted = c - ASCII_CONV;

        encrypted = Encrypt_Decrypt_Cycle(encrypted);

        Enigma_IO::encrypted_char(encrypted);
    }
    return;
}

//===========================================================================

// Rotate next... maybe.
void Enigma::Rotate_Next_Maybe(int index) {

    if (Rotor_Chain[index].Rotate_Next_Rotor() &&
        index < Rotor_Chain_Size - 1)
        Rotor_Chain[index+1].Rotate();
}


// Starred comments - minor comments that would be distracting in line:

// *1 The reason it works is that even if other kinds of files are read in
// in the 3rd pos instead of a rotor, the program will notice and exit.

// *2 Because of the way my rotors are set up with their starting 
// positions, which when being read in requires the number of rotors 
// (legacy from previous build, but kept it because it is in fact 
// a good idea for deciding whether pos file is adequate AT READIN,
// and not at construction), this is needed - it is not a member
// because we only need it temporarily, no use keeping around.

// *3 I first rotate the rightmost Rotor, and then see if the next rotor
// was engaged (if notch is in pos 0), and then rotate that if so. 
// This is in line with the first, more detailed description of how
// rotors rotate one another, but not in line with the odometer comparison;
// in odometers, when 9 reaches the top position (before rotation), the two
// cylinders get connected via a notch, and then rotate together. This would
// be modelled by a reverse ordering of the steps described above.

 