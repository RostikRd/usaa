#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PIZZA 100
#define MAX_NAME_LEN 101

struct pizza {
    char name[MAX_NAME_LEN];
    float price;
};

// Функція для зчитування піц
int read_pizza_list(struct pizza pizzas[]) {
    int count = 0;

    // Зчитуємо піци поки не досягнемо максимальну кількість або не зустрінемо неправильне введення
    while (count < MAX_PIZZA) {
        if (scanf("%100[^\n]%*c", pizzas[count].name) != 1) break;
        if (scanf("%f%*c", &pizzas[count].price) != 1 || pizzas[count].price <= 0) break;
        count++;
    }

    return count;
}

// Функція для порівняння двох піц (для сортування)
int compare_pizza(const void *a, const void *b) {
    struct pizza *pizzaA = (struct pizza *)a;
    struct pizza *pizzaB = (struct pizza *)b;

    // Порівняння за ціною
    if (pizzaA->price != pizzaB->price) {
        return (pizzaA->price > pizzaB->price) - (pizzaA->price < pizzaB->price);
    }
    return strcmp(pizzaA->name, pizzaB->name);
}

// Функція для сортування списку піц
void sort_pizzas(struct pizza pizzas[], int count) {
    qsort(pizzas, count, sizeof(struct pizza), compare_pizza);
}

// Функція для виведення списку піц
void print_pizza_list(struct pizza pizzas[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n%.6f\n", pizzas[i].name, pizzas[i].price);
    }
}

int main() {
    struct pizza pizzas[MAX_PIZZA];
    int count = read_pizza_list(pizzas);
    sort_pizzas(pizzas, count);
    print_pizza_list(pizzas, count);
    return 0;
}
