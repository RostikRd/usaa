#include "compressor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 4096
#define BUFFER_SIZE 18

//функція для считання файлу в память
unsigned char* read_file_in_memory(const char* file_name, size_t* size) {
    FILE* file = fopen(file_name, "rb"); //rb = readbinary

    if (!file) {
        return NULL;
    }
    //переміщуємо вказівник в кінець файлу
    fseek(file, 0, SEEK_END);
    *size = ftell(file); // отримуєм розмір файлу
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = malloc(*size);

    if (!buffer) {

        fclose(file);

        return NULL;
    }
    //перевірка чи цілий файл прочитаний і кількість прочитаних байтів дорівнює розміру файлу
    if (fread(buffer, 1, *size, file) != *size) {
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file);
    //вертається бафер що містить вміст файлу
    return buffer;
}

// Helper function to write memory to a file
int write_memory_in_file(const char* file_name, const unsigned char* inf, size_t size) {
    FILE* file = fopen(file_name, "wb");//wb = write binary

    if (!file) {
        return -1;
    }

    /* Записує дані з буфера `inf` у файл. Параметри:
        - `inf` — вказівник на дані для запису.
        - `1` — розмір одного елемента (1 байт).
     - `size` — кількість елементів для запису.
     */
    fwrite(inf, 1, size, file);

    fclose(file);
    return 0;
}

//Run Length Encoding
//aaa => (3, a)
int compress_1(const char* input_file_name, const char* output_file_name) {
    size_t size;
    unsigned char* input = read_file_in_memory(input_file_name, &size);

    if (!input) {
        return -1;
    }
    //alokovanie pamate
    unsigned char* output = malloc(size * 2);
    if (!output) {
        free(input); //uvoľnenie pamäte
        return -1;
    }

    size_t indx = 0;

    for (size_t i = 0; i < size; ++i) {
        unsigned char count = 1;
        //pocita pocet symbolov ktory opakuju
        while (i + 1 < size && input[i] == input[i + 1] && count < 255) {
            count++;
            i++;
        }
        output[indx++] = count;
        output[indx++] = input[i];
    }

    free(input);

    int result = write_memory_in_file(output_file_name, output, indx);
    free(output);
//vrati velkost dat v inom pripade -1
    return result == 0 ? indx : (size_t)-1;

}

int decompress_1(const char* input_file_name, const char* output_file_name) {
    size_t size;

    unsigned char *input = read_file_in_memory(input_file_name, &size);

    if (!input) {
        return -1;
    }

    unsigned char *output = malloc(size * 255);
    if (!output) {
        free(input);
        return -1;
    }

    size_t indx = 0;
    //vykonáva dekompresiu údajov
    for (size_t i = 0; i < size; i += 2) {
        unsigned char count = input[i];
        unsigned char value = input[i + 1];
        for (unsigned char j = 0; j < count; ++j) {
            output[indx++] = value;
        }
    }

    free(input);

    int result = write_memory_in_file(output_file_name, output, indx);
    free(output);

    return result == 0 ? indx : (size_t)-1;
}
//LZ77
int compress_2(const char* input_file_name, const char* output_file_name) {
    size_t size;
    unsigned char* input = read_file_in_memory(input_file_name, &size);

    if (!input) {
        return -1;
    }

    unsigned char* output = malloc(size * 2);
    if (!output) {
        free(input);
        return -1;
    }

    size_t indx2 = 0;
    size_t i = 0;

    while (i < size) {
        size_t match_length = 0, match_distance = 0;
        size_t start = (i < SIZE) ? 0 : i - SIZE;
        for (size_t j = start; j < i; ++j) {
            size_t k = 0;
            while (k < BUFFER_SIZE && i + k < size && input[j + k] == input[i + k]) {
                k++;
            }
            if (k > match_length) {
                match_length = k;
                match_distance = i - j;
            }
        }

        if (match_length >= 3) {
            output[indx2++] = 0x80 | (match_distance >> 8);
            output[indx2++] = match_distance & 0xFF;
            output[indx2++] = match_length;
            i += match_length;
        } else {
            output[indx2++] = input[i++];
        }
    }

    free(input);
    int result = write_memory_in_file(output_file_name, output, indx2);
    free(output);
    return result == 0 ? indx2 : (size_t)-1;
}

int decompress_2(const char* input_file_name, const char* output_file_name) {
    size_t size;
    unsigned char* input = read_file_in_memory(input_file_name, &size);

    if (!input) {
        return -1;
    }

    unsigned char* output = malloc(size * 255);
    if (!output) {
        free(input);
        return -1;
    }

    size_t indx2 = 0;
    size_t i = 0;

    while (i < size) {
        if (input[i] & 0x80) {
            size_t match_distance = ((input[i] & 0x7F) << 8) | input[i + 1];
            size_t match_length = input[i + 2];
            for (size_t j = 0; j < match_length; ++j) {
                output[indx2] = output[indx2 - match_distance];
                indx2++;
            }
            i += 3;
        } else {
            output[indx2++] = input[i++];
        }
    }

    free(input);
    int result = write_memory_in_file(output_file_name, output, indx2);
    free(output);

    return result == 0 ? indx2 : (size_t)-1;
}
