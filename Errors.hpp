#ifndef ERROR_H
#define ERROR_H

// A function declaration includes std::string so appropriate here
#include<string>

// Error codes
#define INSUFFICIENT_NUMBER_OF_PARAMETERS         1
#define INVALID_INPUT_CHARACTER                   2
#define INVALID_INDEX                             3
#define NON_NUMERIC_CHARACTER                     4
#define IMPOSSIBLE_PLUGBOARD_CONFIGURATION        5
#define INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS  6
#define INVALID_ROTOR_MAPPING                     7
#define NO_ROTOR_STARTING_POSITION                8
#define INVALID_REFLECTOR_MAPPING                 9
#define INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS  10
#define ERROR_OPENING_CONFIGURATION_FILE          11
#define UNKNOWN_FILE_EXTENSION                    12
#define INCORRECT_FILE_ORDER                      13
#define NO_ERROR                                  0

// Error namespace for the overoaded error_description function which
// returns the appropriate error message based on inputs and the
// file_type_message function which outputs the filetype.
namespace Errors {

void error_description(int const error, char* const filename);

void error_description(char* const filename, int size);

void error_description(int const error, char c);

void error_description(int const error,char* const filename, int input_to_map, int ltr_num, int index);

void error_description(int const error, char* const filename, int size);

void error_description(int filetype);

std::string file_type_message(char* const filename);
}

#endif