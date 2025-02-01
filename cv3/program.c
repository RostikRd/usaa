#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 10

struct stack {
    float values[STACK_SIZE];
    int size;
};

void init_stack(struct stack* s) {
    memset(s, 0, sizeof(struct stack));
}

void push_stack(struct stack* s, float value) {
    if (s->size < STACK_SIZE) {     // Перевіряє, чи є місце в стеці
        s->values[s->size] = value; // Додає значення в стек
        s->size += 1;               // Збільшує розмір стеку
    } else {
        printf("full stack\n");
        exit (0);
    }
}

float pop_stack(struct stack* s) {
    if (s->size > 0) {              // Перевіряє, чи є значення в стеці
        s->size -= 1;               // Зменшує розмір стеку
        return s->values[s->size];  // Повертає верхнє значення стеку
    } else {
        printf("Error: Not enough values in the stack\n");
        exit(1);
    }
}

void print_stack(struct stack* s) {
    for (int i = 0; i < s->size; ++i) {
        printf("%.2f ", s->values[i]);
    }
    printf("\n");
}

int is_number(char* input, float* number) {
    char* end;
    *number = strtof(input, &end);  // Перетворює рядок на число з плаваючою точкою
    return end != input && *end == '\0';
}

void process_operator(struct stack* s, char operator) {
    if (s->size < 2) {   // Перевіряє, чи є достатньо значень для операції
        printf("not enough operands\n");
        exit(0);
    }

    float b = pop_stack(s);
    float a = pop_stack(s);
    float result;

    if (operator == '+') {
        result = a + b;
    } else if (operator == '-') {
        result = a - b;
    } else if (operator == '*') {
        result = a * b;
    } else if (operator == '/') {
        if (b != 0) {
            result = a / b;
        } else {
            printf("division by zero\n");
            exit(0);
        }
    } else {
        printf("bad input\n");
        exit(0);
    }

    push_stack(s, result);
}

int main() {
    struct stack my_stack;
    init_stack(&my_stack);

    char input[100];
    int valid_input = 1; // Флаг для правильності вводу

    while (fgets(input, sizeof(input), stdin)) {

        input[strcspn(input, "\n")] = 0;

        float number;
        if (is_number(input, &number)) {
            push_stack(&my_stack, number);
        } else if (strlen(input) == 1) {
            char operator = input[0];
            process_operator(&my_stack, operator);
        }
        else {
            printf("bad input\n");
            valid_input = 0; // Некоректний ввід
            break;
        }
        print_stack(&my_stack);
    }
    
    if (valid_input && my_stack.size == 1) {
        printf("no input\n");
    }

    return 0;
}
