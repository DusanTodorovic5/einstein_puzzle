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

/// @brief Types of tree printing
typedef enum print_type_e {
    HORIZONTAL = 0,
    VERTICAL = 1
} print_type;

/// @brief Simple utility structure containing two unsigned chars
typedef struct pair_t {
    int first;
    int second;
} pair;

/// @brief Relationship type enumeratable
typedef enum relationship_type_t {
    PAIRED = 0,
    NOT_PAIRED,
    END,
    UKNOWN
} relationship_type;

/// @brief Relationship structure of a concept, contains the index of left and right concept as well as relationship between them
typedef struct relationship_t {
    pair left;
    pair right;
    relationship_type type;
} relationship;

/// @brief Structure containing concept data including pointer to name of a concept in 2D array and their relationships
typedef struct concepts_t {
    int number_of_groups;
    int number_of_concepts;
    char*** concepts;
    relationship* relationships;
} concepts;

/// @brief Tree node structure containing table of concepts and pointer to children
typedef struct node_t {
    int row_size;
    int col_size;
    int children_size;
    int level;
    int** table;
    struct node_t** children; 
} node;

/// @brief Structure for linked list(stack and queue) for tree nodes
typedef struct linked_node_t {
    node* data;
    struct linked_node_t* next;
} linked_node;

/// @brief Contains the queue of indexes for avaliable relationships
typedef struct linked_concept_t {
    int row;
    int col;
    struct linked_concept_t* next;
} linked_concept;



/*
 *
 * LOADING CONCEPTS
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
/// @param data Pointer to concepts structure containing data
/// @return Returns NULL in case of an error, otherwise it returns array of relationships that is NULL terminated
relationship* load_relationships(FILE* file_handle, concepts* data);

/// @brief Deletes the allocated memory from tree
/// @param data Concepts to be deleted
void cleanup_concepts(concepts* data);


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

/*
 *
 * TABLE/MAP OPERATIONS
 * 
*/

/// @brief Returns pointer to the string on given index inside concepts structure
/// @param index Location of desired string
/// @param data Structure containing concepts
/// @return Returns the pointer to the string. SHOULD NOT BE FREED.
char* string_from_index(pair index, concepts* data);

/// @brief Returns the location of given string inside concepts structure
/// @param string Desired string
/// @param data Structure containing concepts
/// @return Returns the location of string or {-1,-1} if its non-existent
pair index_from_string(char* string, concepts* data);

/*
 *
 * NODE OPERATIONS
 * 
*/

/// @brief Creates decision tree and returns pointer to the root of a tree
/// @param data Concepts which will be taken in consideration
/// @return pointer to the root of a tree
node* populate(concepts* data);

/// @brief Prints the tree from node given as root, either as horizontal(check windows TREE command) or vertically
/// @param root Pointer to the first node to be printed
/// @param type Printing type, horizontal or vertical
void print(node* root, concepts* data, print_type type);

/// @brief Prints the node in 1 line
/// @param root node to be printed
void print_node(node* root, concepts* data);

/// @brief Copies the given node and returns pointer to new node without copying the children
/// @param src Node to be copied
/// @return Copied node
node* copy_node(node* src);

/// @brief Returns the pointer to all relationships avaliable for children of given node
/// @param src Node for which we want to see avaliable relationships
/// @param data Structure containing all the relationships
/// @return Returns the list of avaliable relationships, that are not used already
linked_concept* get_avaliable_concepts(node* src, concepts* data);

/// @brief Checks if the progress for a game can be continued from given node
/// @param src Node to be checked
/// @param data Concepts data on which the condition will be checked
/// @return Returns 0 if the condition is not met or 1 if the condition is met
int can_continue(node* src, concepts* data);

/// @brief Checks whether the given node is a solution to the puzzle
/// @param src Node to be checked
/// @param data Concepts data on which the condition will be checked
/// @return Returns 0 if the node is not solution, otherwise 1
int is_solution(node* src, concepts* data);

/// @brief Prints all the nodes that are solution
/// @param root Root node of the tree to be printed
/// @param data Concepts data on which the condition will be checked
void print_solutions(node* root, concepts* data);

/// @brief Deletes the allocated memory from tree
/// @param root Root of a tree to delete
void cleanup_tree(node* root);

/// @brief Deletes the allocated memory from node
/// @param src Node to be deleted
void cleanup_node(node* src);

/*
 * 
 * LINKED LIST OPERATIONS
 * 
*/

/// @brief Pops the first element in list, acts as stack
/// @param list List on which the operation will be executed
/// @return Returns the popped node
node* pop(linked_node** list);

/// @brief Removes the last node in list, acts as queue
/// @param list List on which the operation will be executed
/// @return Returns the removed node
node* pop_back(linked_node** list);

/// @brief Pushes the node at the start of the list
/// @param list List on which the operation will be executed
void push(linked_node** list, node* data);

/// @brief Deletes the linked list and all of it nodes. Frees up memory
/// @param list List on which the delete will be executed
void delete(linked_node* list);

/// @brief Pushes row and col to queue of indexes of relationships
/// @param list List on which the action will be executed
/// @param row Row
/// @param col Col
void push_concept(linked_concept** list, int row, int col);

/// @brief Removes row and col from given queue and returns the values
/// @param list List on which the action will be executed
/// @return Returns the pair where first is row and second is col
pair pop_concept(linked_concept** list);

#endif