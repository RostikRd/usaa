#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const char* expr;
#define num_p 3.141592

void skip_space() {
    while (*expr == ' ') expr++;
}

int check_zatvorky(const char* input) {
    int balance = 0;
    while (*input) {
        if (*input == '(') balance++;
        if (*input == ')') balance--;
        if (balance < 0) return 0;
        input++;
    }
    return balance == 0;
}

double reading_num() {
    skip_space();
    char* endptr;
    double value = strtod(expr, &endptr);
    if (expr == endptr) {
        printf("invalid format\n");
        exit(EXIT_FAILURE);
    }
    expr = endptr;
    return value;
}

double calculation_trigonometry() {
    skip_space();
    if (*expr == '(') {
        expr++;
        double result = main_calculation(expr);
        skip_space();
        if (*expr == ')') expr++;
        else {
            printf("wrong parentheses\n");
            exit(EXIT_FAILURE);
        }
        return result;
    } else if (isalpha(*expr)) {
        char func[10];
        int i = 0;
        while (isalpha(*expr) && i < 9) {
            func[i++] = *expr++;
        }
        func[i] = '\0';
        double value = calculation_trigonometry();
        if (strcmp(func, "sin") == 0) return sin(value * num_p / 180);
        if (strcmp(func, "cos") == 0) return cos(value * num_p / 180);
        if (strcmp(func, "sqrt") == 0) {
            if (value < 0) {
                printf("root of negative number\n");
                exit(EXIT_FAILURE);
            }
            return sqrt(value);
        }
        if (strcmp(func, "log") == 0) {
            if (value <= 0) {
                printf("logarithm of non-positive number\n");
                exit(EXIT_FAILURE);
            }
            return log10(value);
        }
        printf("unknown function %s\n", func);
        exit(EXIT_FAILURE);
    }
    return reading_num();
}

double calculation_exponent() {
    double base = calculation_trigonometry();
    skip_space();
    while (*expr == '^') {
        expr++;
        base = pow(base, calculation_trigonometry());
    }
    return base;
}

double calculation_divide_multi() {
    double value = calculation_exponent();
    skip_space();
    while (*expr == '*' || *expr == '/') {
        char op = *expr++;
        double next = calculation_exponent();
        if (op == '/' && next == 0) {
            printf("division by zero\n");
            exit(EXIT_FAILURE);
        }
        if (op == '*') value *= next;
        else value /= next;
    }
    return value;
}

double main_calculation(const char* input) {
    expr = input;
    double value = calculation_divide_multi();
    skip_space();
    while (*expr == '+' || *expr == '-') {
        char op = *expr++;
        double next = calculation_divide_multi();
        if (op == '+') value += next;
        else value -= next;
    }
    return value;
}
