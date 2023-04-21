#ifndef DEFINES_HEADER
#define DEFINES_HEADER

/*
 * 
 * Header containing definitions of all 
 * structures and functions used in Einstein Puzzle
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Return function error codes
typedef enum error_code_e {
    SUCCESS = 0,
    FILE_OPEN_ERROR = 1,
    FILE_FORMAT_ERROR = 2
} error_code;

/// @brief Relationship type enumeratable
typedef enum relationship_type_t {
    PAIRED = 0,
    NOT_PAIRED,
    UKNOWN
} relationship_type;

/// @brief Relationship structure of a concept, contains the name of left and right concept as well as relationship between them
typedef struct relationship_t {
    char* left_concept;
    char* right_concept;
    relationship_type type;
} relationship;

/// @brief Structure containing concept data including pointer to name of a concept in 2D array and their relationships
typedef struct concepts_t {
    int number_of_groups;
    int number_of_concepts;
    char*** concepts;
    relationship* relationships;
} concepts;

/*
 *
 * FUNCTIONS DEFINITIONS FOR LOADING CONCEPTS
 * 
*/

/// @brief Loads concepts data from file and stores it in concept parameter. Returns error code
/// @param filename Name of file to load concepts from
/// @param concept Concept reference, structure in which the concepts will be stored
/// @return Returns error code or SUCCESS
error_code load_file(concepts** concept, char* filename);

/// @brief Loads concepts data from stdin and stores it in concept parameter. Returns error code
error_code load(concepts** concept);

/// @brief Loads the number of concept groups
/// @param file_handle Pointer to the opened file
/// @return Returns the number of concept groups, or 0 in case of an error
int load_number_of_groups(FILE* file_handle);

/// @brief Loads the number of concepts per group
/// @param file_handle Pointer to the opened file
/// @return Returns the number of concepts per group, or 0 in case of an error
int load_number_of_concepts(FILE* file_handle);

/// @brief Loads concepts from a given file
/// @param file_handle Pointer to the opened file
/// @return Returns NULL in case of an error, otherwise it returns 2D array containing concepts
char*** load_concepts(int number_of_groups, int number_per_group, FILE* file_handle);

/// @brief Loads concept's relationships from given file
/// @param file_handle Pointer to the opened file
/// @return Returns NULL in case of an error, otherwise it returns array of relationships that is NULL terminated
relationship* load_relationships(FILE* file_handle);


/*
 *
 * CONVERSIONS
 * 
*/

/// @brief Returns the relationship type corresponding to symbol
/// @param symbol Character of type, can be + or -
/// @return Returns PAIRED in case of +, NOT_PAIRED in case of - and UKNOWN in rest of cases
relationship_type char_to_relationship_type(char symbol);

/// @brief Returns the character corresponding to relationship type
/// @param type Relationship type
/// @return Returns + in case of PAIRED, - in case of NOT_PAIRED and \0 in case of UKNOWN
char relationship_type_to_char(relationship_type type);

#endif