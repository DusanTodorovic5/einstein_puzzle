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

    linked_node* queue = NULL;
    do {
        linked_relationship* relationships = get_avaliable_relationships(current, data);

        pair avaliable_relationship = pop_relationship(relationships);
        int child_index = 0;
        while (avaliable_relationship.first != -1) {
             for (int i = 0;i < data->number_of_concepts;i++) {
                if (current->table[avaliable_relationship.first][i] == -1) {
                    if (current->children) {
                        current->children = (node**)realloc(current->children, sizeof(node*) * (child_index + 1));
                    } else {
                        current->children = (node**)malloc(sizeof(node*));
                    }

                    current->children[child_index] = copy_node(current);
                    current->children[child_index]->table[avaliable_relationship.first][i] = avaliable_relationship.second;
                    
                    push(&queue, current->children[child_index++]);
                }
             }

            avaliable_relationship = pop_relationship(relationships);
        }
    } while ((current = pop_back(&queue)));

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


linked_relationship* get_avaliable_relationships(node* src, concepts* data) {
    linked_relationship* list = NULL;

    for (int i = 1;i < data->number_of_groups;i++) {
        for (int j = 0;j < data->number_of_concepts;j++) {
            int found = 0;
            for (int t = 0;t < src->row_size;t++) {
                if (src->table[i][t] == j) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                push_relationship(&list, i, j);
            }
        }
    }

    return list;
}