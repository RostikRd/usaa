#include "calculator.h"
#include <stdio.h>

int main() {
    char input[length_of_exercise];
    printf("Exercise: ");
    fgets(input, length_of_exercise, stdin);
    if (!check_zatvorky(input)) {
        printf("Mismatched parentheses\n");
        return 1;
    }
    printf("Result: %.2lf\n", main_calculation(input));
    return 0;
}
