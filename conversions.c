#include "defs.h"

char relationship_type_to_char(relationship_type type) {
    switch (type) {
        case PAIRED: return '+';
        case NOT_PAIRED: return '-';
        default: return '\0';
    }
}

relationship_type char_to_relationship_type(char symbol) {
    switch (symbol) {
        case '+': return PAIRED;
        case '-': return NOT_PAIRED;
        default: return UKNOWN;
    }
}