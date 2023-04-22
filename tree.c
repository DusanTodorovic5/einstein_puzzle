#include "defs.h"

node* populate(concepts* data) {
    node* parent = NULL;

    node* current = (node*)malloc(sizeof(node));
    node* root = current;

    current->table = (pair**)malloc(sizeof(pair*) * data->number_of_groups);
    current->children = NULL;
    // root table initialization
    for (int i=0;i<data->number_of_groups;i++) {
        current->table[i] = (pair*)malloc(sizeof(pair) * data->number_of_concepts);
        
        for (int j=0;j<data->number_of_concepts;j++) {
            if (i) {
                current->table[i][j] = -1;
            }
            else {
                current->table[i][j] = j;
            }
        } 
    }




    return root;
}

void print(node* root, print_type type) {

}

node* copy_node(node* src) {
    if (src == NULL || src->row_size == 0) {
        return NULL;
    }

    node* dst = (node*)malloc(sizeof(node));
    
    dst->children = NULL;
    dst->row_size = src->row_size;
    dst->col_size = src->col_size;

    dst->table = (char**)malloc(sizeof(char*) * dst->row_size);
    for (int i=0;i<dst->row_size;i++) {
        dst->table[i] = (char*)malloc(sizeof(char) * dst->col_size);

        memcpy(dst->table[i], src->table[i], dst->col_size);
    }

    return dst;
}