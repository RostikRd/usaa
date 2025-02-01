#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Prevedie čísla na písmená alebo ponechá malé písmená
char convert(char c) {
    switch (c) {
        case '0': return 'o';
        case '1': return 'i';
        case '2': return 'z';
        case '3': return 'e';
        case '4': return 'a';
        case '5': return 's';
        case '6': return 'b';
        case '7': return 't';
        case '8': return 'b';
        case '9': return 'q';
        default: return tolower(c);
    }
}
//Funkcia na kontrolu, či reťazec 'name_pizza' obsahuje podreťazec 'ingredient'
int contains_substring(char *name_pizza, char *ingredient) {
    int len_piz = strlen(name_pizza);
    int len_ing = strlen(ingredient);
    int i, j;

    //prehľadávať každý znak v name_pizza
    for (i = 0; i <= len_piz - len_ing; i++) {
        int found = 1; //Predpokladajme, že sme našli
        for (j = 0; j < len_ing; j++) {
            if (convert(name_pizza[i + j]) != convert(ingredient[j])) {
                found = 0;
                break;
            }
        }
        if (found) return 1;
    }
    return 0;
}
int main() {
    char new_price[10];
    char food_name[100];
    double value;
    int indx = 0;
    char ingredient[100];
    char price[10];

    printf("Zadaj hladanu surovinu:\n");
    if (!fgets(ingredient, sizeof(ingredient), stdin)) {
        return 1;
    }
    ingredient[strcspn(ingredient, "\n")] = '\0';

    printf("Zadaj jedalny listok:\n");
    while (fgets(food_name, sizeof(food_name), stdin)) {
        food_name[strcspn(food_name, "\n")] = '\0';
        if (!fgets(price, sizeof(price), stdin)) {
            break;
        }
        price[strcspn(price, "\n")] = '\0';

        sscanf(price, "%lf", &value);
        sprintf(new_price, "%.2f", value);

        if (contains_substring(food_name, ingredient)) {
            printf("%s\n%s\n", food_name, new_price);
        }

        indx++;
    }

    printf("Nacitanych %d poloziek.\n", indx);

    return 0;
}
