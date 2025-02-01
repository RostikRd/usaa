#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <stdio.h>
#include <stdlib.h>

/**
 * Skomprimuje súbor s názvom input_file_name pomocou kompresného algoritmu 1
 * a zapíše do súboru s názvom output_file_name
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov skomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int compress_1(const char* input_file_name, const char* output_file_name);
/**
 * Dekomprimuje súbor skomprimovaný pomocou algoritmu 1 in a zapíše do súboru out.
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov deomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int decompress_1(const char* input_file_name, const char* output_file_name);
/**
 * Skomprimuje súbor s názvom input_file_name pomocou kompresného algoritmu 2
 * a zapíše do súboru s názvom output_file_name
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov skomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int compress_2(const char* input_file_name, const char* output_file_name);
/**
 * Dekomprimuje súbor skomprimovaný pomocou algoritmu 2 in a zapíše do súboru out.
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov deomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int decompress_2(const char* input_file_name, const char* output_file_name);

#endif // COMPRESSOR_H
