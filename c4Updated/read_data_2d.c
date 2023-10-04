#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./read_data_2d <input filename>\n");
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[1];
    int **data;
    int rows, cols;

    data = read_2d_array_from_file(filename, &rows, &cols);
    print_2d_memory(data, rows, cols);
    free_2d_array(data);

    return 0;
}
