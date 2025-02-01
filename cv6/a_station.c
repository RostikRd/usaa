#include "a_station.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Функція для створення нової станції
struct station* create_station() {
    struct station* new_station = (struct station*)calloc(1, sizeof(struct station));
    new_station->tracks = (struct car**)calloc(STATION_SIZE, sizeof(struct car*));
    new_station->track_count = STATION_SIZE;
    return new_station;
}

// Функція для звільнення пам'яті, виділеної під станцію
void destroy_station(struct station* station) {
    if (station) {
        for (int i = 0; i < station->track_count; i++) {
            struct car* current = station->tracks[i];
            while (current) {
                struct car* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(station->tracks);
        free(station);
    }
}

// Хеш-функція для вибору позиції в масиві станцій
int select_track(struct station* station, const char* target) {
    unsigned long hash = 5381;
    int c;

    while ((c = *target++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % station->track_count;
}

// Функція для додавання або оновлення запису про станцію
void add_target_capacity(struct station* station, const char* target, int capacity) {
    int track = select_track(station, target);
    struct car* current = station->tracks[track];

    // Перевірка, чи вже існує запис про цю станцію
    while (current != NULL) {
        if (strcmp(current->value, target) == 0) {
            current->capacity += capacity; // Збільшити кількість пасажирів
            return;
        }
        current = current->next;
    }

    // Якщо запису немає, створюємо новий
    struct car* new_car = (struct car*)malloc(sizeof(struct car));
    strncpy(new_car->value, target, TARGET_SIZE);
    new_car->capacity = capacity;
    new_car->next = station->tracks[track];
    station->tracks[track] = new_car; // Додаємо на початок списку
}

// Функція для отримання місткості за назвою станції
int get_target_capacity(struct station* station, const char* target) {
    int track = select_track(station, target);
    struct car* current = station->tracks[track];

    while (current != NULL) {
        if (strcmp(current->value, target) == 0) {
            return current->capacity; // Повернути місткість
        }
        current = current->next;
    }

    return 0; // Якщо запису немає
}

// Функція для підрахунку кількості цільових станцій
int count_targets(struct station* station) {
    int count = 0;

    for (int i = 0; i < station->track_count; i++) {
        struct car* current = station->tracks[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
    }

    return count;
}

// Функція для підрахунку загальної місткості всіх станцій
int count_capacity(struct station* station) {
    int total_capacity = 0;

    for (int i = 0; i < station->track_count; i++) {
        struct car* current = station->tracks[i];
        while (current != NULL) {
            total_capacity += current->capacity;
            current = current->next;
        }
    }

    return total_capacity;
}
