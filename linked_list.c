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

node* pop_back(linked_node** list) {
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

void push_relationship(linked_relationship** list, int row, int col) {
    if (list == NULL) {
        return;
    }

    linked_relationship* new = (linked_relationship*)malloc(sizeof(linked_relationship));
    new->row = row;
    new->col = col;
    new->next = (*list);
    *list = new;
}

pair pop_relationship(linked_relationship** list) {
    pair ret_index;
    ret_index.first = ret_index.second = -1;
    if (list == NULL || (*list) == NULL) {
        return ret_index;
    }

    linked_relationship* first = *list;

    pair ret_index;
    ret_index.first = first->row;
    ret_index.second = first->col;

    *list = (*list)->next;
    free(first);

    return ret_index;
}