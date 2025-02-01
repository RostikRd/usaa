#include "a_train.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car* add_car(struct car* first, const char* target) {
    struct car* newcar = calloc(1, sizeof(struct car));
    if (newcar == NULL) {
        return first;
    }
    strcpy(newcar->value, target); // Копіювання назви станції в новий вагон

    if (first == NULL) {
        return newcar;
    }

    struct car* this = first;
    while (this->next != NULL) {// Проходимо список до останнього вагону
        this = this->next;
    }
    this->next = newcar; // Прив'язуємо новий вагон до кінця поїзда

    return first;// Повертаємо вказівник на перший вагон
}

void print_train(struct car* first) {
    struct car* this = first;
    while (this != NULL) {
        printf("Stanica: %s\n", this->value);
        this = this->next;
    }
}

void cancel_train(struct car* first) {
    struct car* this = first;
    while (this != NULL) {
        struct car* next = this->next; // Зберігаємо вказівник на наступний вагон
        free(this);// Звільняємо пам'ять для поточного вагону
        this = next;  // Переходимо до наступного вагону
    }
}

struct car* clear_train(struct car* first, const char* target) {
    struct car* this = first;
    struct car* prev = NULL;

    while (this != NULL) {
        if (strcmp(this->value, target) == 0) { // перевірка на те чи назва станції є та сама що і цільова
            if (prev == NULL) { // якщо це перший вагон
                struct car* temp = this;
                first = this->next;
                this = this->next;
                free(temp);
            } else { // якщо це не перший вагон
                struct car* temp = this;
                prev->next = this->next;
                this = this->next;
                free(temp);
            }
        } else {
            prev = this;      // Оновлюємо попередній вагон
            this = this->next;// Переходимо до наступного вагону
        }
    }
    return first;
}
