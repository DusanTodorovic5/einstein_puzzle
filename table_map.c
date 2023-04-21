#include "defs.h"

char* string_from_index(pair index, concepts* data) {
    if (index.first < data->number_of_groups && index.first < data->number_of_concepts) {
        return data->concepts[index.first][index.second];
    }
    
    return NULL;
}

pair index_from_string(char* string, concepts* data) {
    for (int i=0;i<data->number_of_groups;i++) {
        for (int j=0;j<data->number_of_concepts;j++) {
            if (!strcmp(data->concepts[i][j], string)) {
                pair ret_pair;
                ret_pair.first = i;
                ret_pair.second = j;
                return ret_pair;
            }
        }
    }

    pair ret_pair;
    ret_pair.first = -1;
    ret_pair.second = -1;
    return ret_pair;
}