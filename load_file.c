#include "defs.h"

error_code load_file(concepts** concept, char* filename) {
    FILE *file_handle = filename ? fopen(filename, "r") : stdin;

    if (file_handle == NULL) {
        return FILE_OPEN_ERROR;
    }

    *concept = (concepts*)malloc(sizeof(concepts));

    (*concept)->number_of_groups = load_number_of_groups(file_handle);
    (*concept)->number_of_concepts = load_number_of_concepts(file_handle);

    (*concept)->concepts = load_concepts(
        (*concept)->number_of_groups,
        (*concept)->number_of_concepts,
        file_handle
    );

    (*concept)->relationships = load_relationships(file_handle, *concept);

    fclose(file_handle);

    return 0;
}

error_code load(concepts** concept) {
    return load_file(concept, NULL);
}

int load_number_of_groups(FILE* file_handle) {
    int ret_val = 0;
    return fscanf(file_handle, "%d\n", &ret_val) != 1 ? 0 : ret_val;
}

int load_number_of_concepts(FILE* file_handle) {
    int ret_val = 0;
    return fscanf(file_handle, "%d\n", &ret_val) != 1 ? 0 : ret_val;
}

char*** load_concepts(int number_of_groups, int number_per_group, FILE* file_handle) {
    char temp[128];
    int i = 0;
    int j = 0;
    int ret = 0;

    char*** all_concepts = (char***)malloc(number_of_groups * sizeof(char**));

    for (i = 0;i < number_of_groups;i++) {
        char** group = (char**)malloc(number_per_group * sizeof(char*));

        for (j = 0; j < number_per_group - 1; j++) {
            memset(temp, 0, sizeof(temp));
            ret = fscanf(file_handle, "%[^,],", temp);

            if (ret != 1) {
                free(group);
                return all_concepts;
            }

            size_t len = strlen(temp);

            // remove new line if the string contains it
            if (temp[0] == '\n') {
                for (int i = 0; i < len; i++) {
                    temp[i] = temp[i+1];
                }
                --len;
            }

            // copy the string and set null at the end
            group[j] = (char*)malloc(sizeof(char) * (len + 1));
            strcpy(group[j], temp);
            group[j][len] = '\0';
        }
        
        ret = fscanf(file_handle, "%s", temp);
        if (ret != 1) {
            free(group);
            return all_concepts;
        }
        size_t len = strlen(temp);

        group[j] = (char*)malloc(sizeof(char) * (len+ 1));
        strcpy(group[j], temp);
        group[j][len] = '\0';

        all_concepts[i] = group;
    }

    return all_concepts;
}

relationship* load_relationships(FILE* file_handle, concepts* data) {
    char left[128];
    char symbol;
    char right[128];

    relationship* relationships = NULL;

    int i=0;
    for (;fscanf(file_handle, "%s %c %s", left, &symbol, right) != -1;i++) {
        relationships = (relationship*)(relationships ?
            realloc(relationships, sizeof(relationship) * (i + 1)) :
            malloc(sizeof(relationship))
        );

        relationships[i].type = char_to_relationship_type(symbol);
        relationships[i].left = index_from_string(left, data);
        relationships[i].right = index_from_string(right, data);

        if (relationships[i].left.first == -1 || relationships[i].right.first == -1) {
            free(relationships);
            return NULL;
        }
    }

    if (relationships) {
        relationships = (relationship*)realloc(relationships, sizeof(relationship) * (i + 1));
        relationships[i].type = END;
    }

    return relationships;
}

void cleanup_concepts(concepts* data) {
    for (int i=0;i<data->number_of_groups;i++) {
        for (int j=0;j<data->number_of_concepts;j++) {
            free(data->concepts[i][j]);
        }
        
        free(data->concepts[i]);
    }

    free(data->concepts);
    free(data->relationships);
}