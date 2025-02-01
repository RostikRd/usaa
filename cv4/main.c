#include "a_train.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct car* train = NULL;
    char buffer[SIZE];
    int passengers;

    printf("Zadajte zoznam cieľových staníc a počet cestujúcich.\n");
    printf("Zoznam zakončite prázdnym riadkom.\n");

    while (1) {
        if (!fgets(buffer, SIZE, stdin) || buffer[0] == '\n') {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        if (scanf("%d", &passengers) != 1) {
            fprintf(stderr, "Chyba pri čítaní počtu cestujúcich.\n");
            break;
        }
        getchar(); 

        train = add_car(train, buffer);
    }

    printf("Obsah vlaku:\n");
    print_train(train);

    printf("Zadajte stanicu, ktorá sa má vyradiť:\n");
    if (fgets(buffer, SIZE, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        train = clear_train(train, buffer);
    }
    
    printf("Výsledný vlak bez stanice %s bude:\n", buffer);
    print_train(train);


    cancel_train(train);

    return 0;
}
