#ifndef IO_H
#define IO_H

#include<fstream>
#include<vector>
#include"Constants.hpp"

// Separate namespace for IO functions. I did it this way firstly because
// there was just a lot of code that was going to be copy-pasted between IO 
// operations in the various classes, and this way they are all shared, and
// secondly, because I think it makes the classes that represent the components
// of the enigma machine and the machine itself less cluttered and much more 
// straighforward to read and understand by moving the functions that handle 
// reading in from files and errors out of the class context (while still being 
// called at construction, of course)

namespace Enigma_IO {

    // Reads in settings of any kind from a file; it determines what kind offs
    // file it is based on the extension, and applies the appropriate error
    // checks to it. 
    std::vector<int> read_settings(char* const filename);

    // Checks if input stream opens successfully
    void opener(std::ifstream &in, char* const filename);

    // Checks if character is non-numeric, throws appropriate error if so.
    void non_numeric_checker(char c, char* const filename);

    // Checks if number to be placed in settings is already in it,throws
    // appropriate error and outputs message if it is, otherwise places number 
    // inside settings.
    void check_and_place(std::vector<int> &settings, int ltr_num, int const error_code, char* const filename);

    // Checks if number is legal (between 0 and 25)
    void check_number_legality(int ltr_num, char* const filename);

    // Checks settings for the conditions needed to be well-formed for a plugboard
    void check_plugboard_settings(std::vector<int> const &settings, char* const filename);

    // Checks settings for the conditions needed to be well-formed for a reflector
    void check_reflector_settings(std::vector<int> const &settings, char* const filename);

    // Checks settings for the conditions needed to be well-formed for a rotor
    void check_rotor_settings(std::vector<int> const &settings, char* const filename);

    // Reads in rotor positions; this is dependent on the number of rotors, so it
    // is simpler to have as a separate function using the standard read in than
    // otherwise.
    std::vector<int> read_rotor_positions(char* const filename, int rotors);

    // Checks the number of parameters.
    void check_parameter_number(int argc);

    // Transforms an int into a char.
    char int_to_char(int internal_output);

    // Prints encrypted character (from int to char)
    void encrypted_char(int internal_output);

    // Determines the file type of a given input file, and returns the name
    // of the component to whcih it belongs.
    int file_type(char* const filename);

    // Determines the unique error code belonging to a particular file based
    // on its extension.
    int determine_unique_error_code(int filetype);

    // Checks the settings that were read in, applying the
    // correct operation based on what kind of file it is.
    void check_settings_after_read(std::vector<int> &settings, int filetype, char* const filename);

    void check_file_order(int argc, char **argv);

    void check_console_input(char c);
}

#endif
