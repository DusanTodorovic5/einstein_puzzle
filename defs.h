#ifndef DEFINES_HEADER
#define DEFINES_HEADER

/*
 * 
 * Header containing definitions of all 
 * structures and functions used in Einstein Puzzle
 * 
*/

#include <stdio.h>

enum relationship_type_t {
    PAIRED = 0,
    NOT_PAIRED,
    UKNOWN
};

typedef struct relationship_t {
    char* left_concept;
    char* right_concept;
    relationship_type_t type;
} relationship;

typedef struct concepts_t {
    int n;
    int m;
    char*** concepts;
    relationship* relationships;
} concepts;

void load_from_file(const char* filename, concepts** concept);
int load_number_of_groups(FILE* file_handle);
int load_number_of_concepts(FILE* file_handle);
char** load_concepts(FILE* file_handle);
relationship* load_relationships(FILE* file_handle);



#endif