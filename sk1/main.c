#include "compressor.h"
#include <string.h>

void help() {

    printf("  ./compressor -c1 infile outfile (Compress RLE)\n");
    printf("  ./compressor -d1 infile outfile (Decompress RLE)\n");
    printf("  ./compressor -c2 infile outfile (Compress LZ77)\n");
    printf("  ./compressor -d2 infile outfile (Decompress LZ77)\n");
    printf("  ./compressor -h (show all commands)\n");
}

int main(int argc, char* argv[]) {
    
    if (argc != 4 && !(argc == 2 && strcmp(argv[1], "-h") == 0)) {
        help();
        return 1;
    }

    if (strcmp(argv[1], "-c1") == 0) {
        
        return compress_1(argv[2], argv[3]) >= 0 ? 0 : 1;
        
    } else if (strcmp(argv[1], "-d1") == 0) {
        
        return decompress_1(argv[2], argv[3]) >= 0 ? 0 : 1;
        
    } else if (strcmp(argv[1], "-c2") == 0) {
        
        return compress_2(argv[2], argv[3]) >= 0 ? 0 : 1;
        
    } else if (strcmp(argv[1], "-d2") == 0) {
        
        return decompress_2(argv[2], argv[3]) >= 0 ? 0 : 1;
        
    } else if (strcmp(argv[1], "-h") == 0) {
        
        help();
        return 0;
    } else {
        
        help();
        return 1;
    }
}
