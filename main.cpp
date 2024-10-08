#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "stack.h"

int fprintf_char(FILE *file, void *symbol);

int fprintf_char(FILE *file, void *symbol) {
    return fprintf(file, "%c", *(char *)symbol);
}

// EXAMPLE
int main(void) {
    stack_t *stack = stack_init(DUMP_INIT("stack.log", stack, fprintf_char) 3, sizeof(char));
    if(stack == NULL) {
        printf("Stack initializing error\n");
        return EXIT_FAILURE;
    }

    char symbol = 'a';
    stack_error_t error_code = STACK_SUCCESS;

    error_code = stack_push(&stack, &symbol);
    if(error_code != STACK_SUCCESS && error_code != STACK_EMPTY) {
        printf("Push error\n");
        return EXIT_FAILURE;
    }

    char symbol_copy = 0;
    error_code = stack_pop(&stack, &symbol_copy);
    if(error_code != STACK_SUCCESS && error_code != STACK_EMPTY) {
        printf("Pop error\n");
        return EXIT_FAILURE;
    }

    error_code = stack_destroy(&stack);
    if(error_code != STACK_SUCCESS) {
        printf("Destroying error\n");
        return EXIT_FAILURE;
    }

    return STACK_SUCCESS;
}
