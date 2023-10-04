#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Usage: ./make_data_2d <#rows> <#cols> <low> <high> <output filename>\n");
        exit(EXIT_FAILURE);
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int low = atoi(argv[3]);
    int high = atoi(argv[4]);
    const char* filename = argv[5];

    int** data = create_2d_array(rows, cols, low, high);
    write_2d_array_to_file(data, rows, cols, filename);

    free_2d_array(data);

    return 0;
}
