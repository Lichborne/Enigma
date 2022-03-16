#include<iostream>
#include<string>
#include<cctype>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<iterator>
#include"IO.hpp"
#include"Errors.hpp"
// vector and fstream needed for header file already, so not included twice

//==========================================================================

// This is one large function because breaking it down into subfunctions 
// composed of subfunctions seemed a little silly given that there are already
// four subroutines separated out into functions, which simply get applied
// in a different combination in various cases. 
// Separating out some subsections into their own functions would be hugely 
// inefficient and also, in this case, I think more difficult to read.

 std::vector<int> Enigma_IO::read_settings(char* const filename) {

    std::vector<int> settings = {};

    std::ifstream in;
    int filetype = Enigma_IO::file_type(filename);
    int unique_error_code = Enigma_IO::determine_unique_error_code(filetype);
    char fst, snd;
    int ltr_num;

    Enigma_IO::opener(in, filename);
    
    // Checking for non-numeric characters and outputting the right error
    // message appeared to me to be simpler if we go char-by-char instead
    // of block by block with cin, so that is what I chose to do.
    while ((in.get(fst)).good()) {

        // Skip whitespace.
        if (isspace(fst))
            continue;

        // Check if character is non-numeric.
        Enigma_IO::non_numeric_checker(fst, filename);
        
        if ((in.get(snd)).good()) {

            // If second char is space, we know we read in a single digit.
            if (isspace(snd)) {
                ltr_num = fst - ASCII_NUMS;
                Enigma_IO::check_number_legality(ltr_num, filename);
                Enigma_IO::check_and_place(settings, ltr_num, 
                                unique_error_code, filename);
                continue;
            }
            // Otherwise we read in a double digit int. 
            // (performing appropriate checks).
            Enigma_IO::non_numeric_checker(snd, filename);
            ltr_num = (fst - ASCII_NUMS)*10 + (snd - ASCII_NUMS);
            Enigma_IO::check_number_legality(ltr_num, filename);
            Enigma_IO::check_and_place(settings, ltr_num,  
                             unique_error_code, filename);

        //Else required in this case
        } else {
            ltr_num = fst - ASCII_NUMS;             
            Enigma_IO::check_and_place(settings, ltr_num, 
                            unique_error_code, filename);
        }
    }
    in.close();

    Enigma_IO::check_settings_after_read(settings, filetype, filename);

    return settings;
}

//===========================================================================

void Enigma_IO::opener(std::ifstream &in, char* const filename) {

    in.open(filename);

    if (in.fail()) {
        Errors::error_description(ERROR_OPENING_CONFIGURATION_FILE, filename);
        throw ERROR_OPENING_CONFIGURATION_FILE;
    }

}

//===========================================================================

void Enigma_IO::non_numeric_checker(char c, char* const filename) {

    if (c > '9' || c < '0') {
        Errors::error_description(NON_NUMERIC_CHARACTER, filename);
       throw NON_NUMERIC_CHARACTER; 
    }
}

//===========================================================================

void Enigma_IO::check_and_place(std::vector<int> &settings, int ltr_num, 
                                int const error_code, char* const filename) {

    // For reading rotor positions the checking is skipped because rotors
    // can have the same starting position.
    if (error_code == NO_ERROR || settings.size() >= ALPHABET_SIZE) {
        settings.push_back(ltr_num);
        return;
    }

    std::vector<int>::iterator it = std::find(settings.begin(), 
                                      settings.end(), ltr_num);

    // Check if the number is already in there; if so -> error.
    if (it != settings.end()) {
        int index = std::distance(settings.begin(), it);
        Errors::error_description(error_code, filename, (settings.size()), 
                                                           ltr_num, index);
        throw error_code;
    }
    // Otherwise push back and move on.
    settings.push_back(ltr_num);
}

//===========================================================================

// Checks if number is legal (between 0 and 25)
void Enigma_IO::check_number_legality(int ltr_num, char* const filename) {

    if (ltr_num > 25 || ltr_num < 0) {
        Errors::error_description(INVALID_INDEX, filename);
        throw INVALID_INDEX;
    }
}

//==========================================================================

void Enigma_IO::check_plugboard_settings(std::vector<int> const &settings, char* const filename) {

    if (settings.size() % 2) {
        Errors::error_description(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS,
                                                                filename);
        throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }   
}

//==========================================================================
 
 void Enigma_IO::check_reflector_settings(std::vector<int> const &settings, char* const filename) {

    if (settings.size() != 26) {
        Errors::error_description(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS, 
                                                filename, settings.size());
        throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
}

//==========================================================================


void Enigma_IO::check_rotor_settings(std::vector<int> const &settings, char* const filename) {

    if (settings.size() < 26) {
        Errors::error_description(INVALID_ROTOR_MAPPING, filename);
        throw INVALID_ROTOR_MAPPING;
    }
}

//==========================================================================

std::vector<int> Enigma_IO::read_rotor_positions(char* const filename, int rotors) {
    
    std::vector<int> rotor_positions = Enigma_IO::read_settings(filename);

    // If there are not at least as many rotor position settings as rotors
    // at least one rotor does not ahve a starting position defined.
    if (int(rotor_positions.size()) < rotors) {
        // To record the index of the rotor (left to right) without a pos.
        Errors::error_description(NO_ROTOR_STARTING_POSITION, filename, 
                                                rotor_positions.size());
        throw NO_ROTOR_STARTING_POSITION;
    }
    return rotor_positions;
}

//==========================================================================

void Enigma_IO::check_parameter_number (int argc) {
    char empty[0] = {};
    if (argc < 3) {
        Errors::error_description(INSUFFICIENT_NUMBER_OF_PARAMETERS, empty);
        throw INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }
}

//==========================================================================

char Enigma_IO::int_to_char(int internal_output) {
    
    char output_char = internal_output + ASCII_CONV;
    
    return output_char;
}

//==========================================================================

void Enigma_IO::encrypted_char(int internal_output) {

    std::cout << int_to_char(internal_output);
}

//==========================================================================

int Enigma_IO::file_type(char* const filename) {

    std::string converted(filename);

    auto file_type_checker = [] (std::string &filename, std::string extension) {
        if (filename.length() >= extension.length()) {
            return (0 == filename.compare(filename.length() -
                    extension.length(), extension.length(), extension));
        } else {
            return false;
        }
    };

    if (file_type_checker(converted, ".pb"))
        return PLUGBOARD;
    
    if (file_type_checker(converted, ".rf"))
        return REFLECTOR;

    if (file_type_checker(converted, ".rot"))
        return ROTOR;
    
    if (file_type_checker(converted, ".pos"))
        return POSITIONS;

    // This is a different kind of error than those in the specs
    throw UNKNOWN_FILE_EXTENSION;

    // will never reach here, just to be safe.
    return 0;
}

//==========================================================================

int Enigma_IO::determine_unique_error_code(int filetype) {

    switch (filetype) {
        case PLUGBOARD: 
            return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;

        case REFLECTOR: 
            return INVALID_REFLECTOR_MAPPING;
        
        case ROTOR: 
            return INVALID_ROTOR_MAPPING;
    }
    //for positions, there is no such erorr, only different ones.
    return NO_ERROR;
}

//==========================================================================

void Enigma_IO::check_settings_after_read(std::vector<int> &settings, int filetype, char* const filename) {

    switch (filetype) {
        case PLUGBOARD: 
            Enigma_IO::check_plugboard_settings(settings, filename);
            return;
            
        case REFLECTOR: 
            Enigma_IO::check_reflector_settings(settings, filename);
            return;
            
        case ROTOR:
            Enigma_IO::check_rotor_settings(settings, filename);     
            return; 
    }
}

//==========================================================================

void Enigma_IO::check_file_order(int argc, char **argv) {

    // files start from the first, not the zeroth index!
    if (file_type (argv[1]) != PLUGBOARD) {
        Errors::error_description(PLUGBOARD);
        throw INCORRECT_FILE_ORDER;
    }
    // reflector at index 2
    if (file_type (argv[2]) != REFLECTOR) {
        Errors::error_description(REFLECTOR);
        throw INCORRECT_FILE_ORDER;
    }
    // positions at last index
    if (file_type (argv[argc-1]) != POSITIONS) {
        Errors::error_description(POSITIONS);
        throw INCORRECT_FILE_ORDER;
    }
    // for all indeces between the reflector file and the end, check filetype
    for (int i = 3; i <= argc-2; i++) {
        if (file_type (argv[i]) != ROTOR) {
        Errors::error_description(ROTOR);
        throw INCORRECT_FILE_ORDER;
        }
    }
}

//==========================================================================

void Enigma_IO::check_console_input(char c) {

    if (c < 'A' || c > 'Z') {
            Errors::error_description(INVALID_INPUT_CHARACTER, c);
            throw INVALID_INPUT_CHARACTER;
    }
}

//==========================================================================