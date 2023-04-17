#include "defs.h"

error_code load(concepts** concept, const char* filename) {
    FILE *file_handle = fopen(filename, "r");

    if (file_handle == NULL) {
        return FILE_OPEN_ERROR;
    }

    *concept = (concepts*)malloc(sizeof(concepts));
    concepts* this = concept;

    this->number_of_groups = load_number_of_groups(file_handle);
    this->number_of_concepts = load_number_of_concepts(file_handle);
    this->concepts = load_concepts(file_handle);
    this->relationships = load_relationships(file_handle);

    fclose(file_handle);

    return 0;
}

int load_number_of_groups(FILE* file_handle) {
    char* line = NULL;
    char* end = NULL;
    int ret_val = 0;
    size_t len = 0;
    
    if (getline(&line, len, file_handle) == -1) {
        return 0;
    }

    // returns value in integer format, if end pointer is not null, error happened
    ret_val = strtol(line, end, 10);

    if (end != NULL) {
        ret_val = 0;
    }

    free(line);
    return ret_val;
}

int load_number_of_concepts(FILE* file_handle) {
    return 0;
}

char** load_concepts(FILE* file_handle) {
    return NULL;
}

relationship* load_relationships(FILE* file_handle) {
    return NULL;
}