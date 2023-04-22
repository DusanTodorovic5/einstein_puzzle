#include "defs.h"

node* pop(linked_node** list) {
    if (list == NULL || (*list) == NULL) {
        return NULL;
    }

    linked_node* last = *list;
    node* ret_node = last->data;

    *list = (*list)->next;
    free(last);

    return ret_node;
}

node* remove(linked_node** list) {
    if (list == NULL || (*list) == NULL) {
        return NULL;
    }

    node* ret_node = NULL;

    if ((*list)->next == NULL) {
        ret_node = (*list)->data;
        free((*list));
        *list = NULL;
    } else {
        linked_node* pre_last = *list;
        
        // get the element before last element
        while ((pre_last = (*list)->next)->next->next);

        linked_node* last = pre_last->next;
        pre_last->next = NULL;

        ret_node = last->data;
        free(last);
    }

    return ret_node;
}

void push(linked_node** list, node* data) {
    if (list == NULL || data == NULL) {
        return;
    }

    linked_node* new = (linked_node*)malloc(sizeof(linked_node));
    new->data = data;
    new->next = (*list);
    *list = new;
}

void delete(linked_node* list) {
    while (list) {
        linked_node* curr = list;
        list = list->next;
        
        free(curr);
    }
}