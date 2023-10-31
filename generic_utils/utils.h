#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

/**
 * @file utils.h
 * @author Eskil Lundegårdh
 * @date 16 Okt 2023
 * @brief Utility functions for input
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */

/// @brief Data union to store different data types.
typedef union {
    int   int_value;      
    float float_value;    
    char *string_value;   
    char  char_value;     
} answer_t;

/// Function pointer type for checking user input.
typedef bool (*check_func)(char *);

/// Function pointer type for converting user input.
typedef answer_t (*convert_func)(char *);

/// @brief Ask a question and validate user input.
/// This function asks a question to the user, validates the input using the provided
/// check and convert functions, and returns the result.
/// @param question The question to ask the user.
/// @param check A function to validate the user's input.
/// @param convert A function to convert the validated input.
/// @return The converted result based on user input.
answer_t ask_question(char *question, check_func check, convert_func convert);

/// @brief Ask a question and validate the user input as a string.
/// This function asks a question to the user, validates the input as a non-empty string,
/// and returns the result.
/// @param question The question to ask the user.
/// @return The validated string input from the user.
char *ask_question_string(char *question);

/// @brief Ask a question and validate the user input as an integer.
/// This function asks a question to the user, validates the input as an integer,
/// and returns the result.
/// @param question The question to ask the user.
/// @return The validated integer input from the user.
int ask_question_int(char *question);

/// @brief Ask a question and validate the user input as a shelf identifier.
/// This function asks a question to the user, validates the input as a valid shelf identifier,
/// and returns the result.
/// @param question The question to ask the user.
/// @return The validated shelf identifier input from the user.
char *ask_question_shelf(char *question);
#endif
