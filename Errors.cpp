#include<iostream>
#include<cctype>
#include<cstdlib>
#include"Errors.hpp"
#include"Constants.hpp"
#include"IO.hpp" 

//===========================================================================

// Given an error code, outputs appropriate message to std errstream.
void Errors::error_description(int const error, char* const filename) {

    switch(error) {
        case 1: 
            std::cerr << "usage: enigma plugboard-file reflector-file "
                      << "(<rotor-file>)* rotor-positions\n";
            return;
        case 3: 
            std::cerr << "Invalid index (not 0<x<25) "
                      << Errors::file_type_message(filename)
                      << " file " << filename << std::endl; 
            return;
        case 4: 
            std::cerr << "Non-numeric character " 
                      << Errors::file_type_message(filename)
                      << " file " << filename << std::endl; 
            return;
        case 6: 
            std::cerr << "Incorrect number of parameters in plugboard file "
                      << filename << std::endl;
            return;
        case 7: 
            std::cerr << "Not all inputs mapped in rotor file: " 
                      << filename << std::endl;
            return;
        case 10:
            std::cerr << "Incorrect number of parameters in reflector file "
                      << filename << std::endl;
            return;
        case 11:
            std::cerr << "Error opening the configuration file: " 
                      << filename << std::endl;
            return;
        case 12:
            std::cerr << "<unknown file extension, correct extensions "
                      << "include .pb .rf .rot .pos>" << std::endl;
        case 13: 
            std::cerr << "Incorrect file order.\n"
                      << "usage: enigma plugboard-file reflector-file "
                      << "(<rotor-file>)* rotor-positions\n";
        case 0:
            std::cerr << "No error.\n";
            return;
    }
}

//===========================================================================

void Errors::error_description(int const error, char c) {

    std::cerr << c << " is not a valid input character (input "
              << "characters must be upper case letters A-Z)!\n";
}

//===========================================================================
// "ifs" used here because multiple conditions in one case so would need
// two "switches" anyway.
void Errors::error_description(int const error, char* const filename, int size) {

    if (error == 8) {
        std::cout << "No starting position for rotor " << size
                  << " in rotor position file: " << filename << std::endl;
        return;
    }
    
    if ((error == 10) && (size % 2)) {
        std::cerr << "Incorrect (odd) number of parameters in reflector file "
                  << filename << std::endl;
        return;
    }

    if (error == 10) {
    std::cerr << "Insufficient number of mappings in reflector file: "
              << filename << std::endl;
    }
}

//===========================================================================

void Errors::error_description(int const error, char* const filename, int input_to_map, int ltr_num, int index) {
     switch(error) {
         case 5: 
            std::cerr << "Impossible plugboard configuration: ";
            std::cerr << "Invalid mapping of input " << input_to_map 
                      << " to output " << ltr_num << " (output " << ltr_num
                      << " is already mapped to from input " << index
                      << ") in plugboard file: " << filename << std::endl;
            return;
         case 7: 
            std::cerr << "Invalid mapping of input " << input_to_map 
                      << " to output " << ltr_num << " (output " << ltr_num
                      << " is already mapped to from input " << index 
                      << ") in rotor file: " << filename << std::endl;
            return;
     
        case 9: 
            std::cerr << "Invalid mapping of input " << input_to_map 
                      << " to output " << ltr_num << " (output " << ltr_num
                      << " is already mapped to from input " << index 
                      << ") in reflector file: " << filename << std::endl;
            return;
     }
     
}

//===========================================================================

void Errors::error_description(int filetype) {
    switch(filetype) {
         case PLUGBOARD: 
            std::cerr << "Incorrect file ordering: "
                      << "First file is not a plugboard (.pb) file\n"
                      << "usage: enigma plugboard-file reflector-file "
                      << "(<rotor-file>)* rotor-positions\n";
            return;

         case REFLECTOR: 
            std::cerr << "Incorrect file ordering: "
                      << "Second file is not a reflector(.rf) file\n"
                      << "usage: enigma plugboard-file reflector-file "
                      << "(<rotor-file>)* rotor-positions\n";
            return;

         case ROTOR: 
            std::cerr << "Incorrect file ordering: "
                      << "Files between reflector and positions files "
                      << "are not all positions (.pos) files\n";
            std::cerr << "usage: enigma plugboard-file reflector-file "
                      << "(<rotor-file>)* rotor-positions\n";
            return;

         case POSITIONS: 
            std::cerr << "Incorrect file ordering: "
                      << "Last file is not a positions (.pos) file\n"
                      << "usage: enigma plugboard-file reflector-file "
                      << "(<rotor-file>)* rotor-positions\n";
            return;
    }
}

//===========================================================================

std::string Errors::file_type_message(char* const filename) {

    int filetype = Enigma_IO::file_type(filename);

    if (filetype == PLUGBOARD)
        return ("in plugboard");
    
    if (filetype == REFLECTOR)
        return ("in reflector");

    if (filetype == ROTOR)
        return ("for mapping in rotor");
    
    if (filetype == POSITIONS)
        return ("in rotor positions");
    
    return (" in <unknown file extension, correct extensions include .pb .rf. .rot .pos>");
}

//===========================================================================