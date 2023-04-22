#include "defs.h"

node* populate(concepts* data) {

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

    dst->table = (pair**)malloc(sizeof(pair*) * dst->row_size);
    for (int i=0;i<dst->row_size;i++) {
        dst->table[i] = (pair*)malloc(sizeof(pair) * dst->col_size);

        memcpy(dst->table[i], src->table[i], dst->col_size);
    }

    return dst;
}