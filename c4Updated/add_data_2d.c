#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./add_data_2d <in file1> <in file2> <out filename>\n");
        exit(EXIT_FAILURE);
    }

    int rows1, cols1, rows2, cols2;
    int** data1 = read_2d_array_from_file(argv[1], &rows1, &cols1);
    int** data2 = read_2d_array_from_file(argv[2], &rows2, &cols2);

    if (rows1 != rows2 || cols1 != cols2) {
        printf("Matrix dimensions do not match.\n");
        free_2d_array(data1);
        free_2d_array(data2);
        exit(EXIT_FAILURE);
    }

    int** result = add_2d_arrays(data1, data2, rows1, cols1); // Assuming you have this function in utilities.c
    write_2d_array_to_file(result, rows1, cols1, argv[3]);

    free_2d_array(data1);
    free_2d_array(data2);
    free_2d_array(result);

    return 0;
}
