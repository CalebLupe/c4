// Reads a 2D array from a file and prints it
#include <stdio.h>
#include <stdlib.h>

// This code reads a 2-dimensional array of integers from a file. 
// The first two bytes of the file contain the number of rows and columns of the array. 
// The remaining bytes of the file contain the array elements in row-major order.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./read_data_2d <input filename>\n");
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[1];
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error opening file for reading.\n");
        exit(EXIT_FAILURE);
    }

    int rows, cols;
    if (fread(&rows, sizeof(int), 1, fp) != 1) {
        printf("Error reading rows from file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    if (fread(&cols, sizeof(int), 1, fp) != 1) {
        printf("Error reading cols from file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int** data = malloc(rows * sizeof(int*));
    int* temp = malloc(rows * cols * sizeof(int));
    if (!data || !temp) {
        printf("Error allocating memory.\n");
        free(data);
        free(temp);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        data[i] = temp + i * cols;
        if (fread(data[i], sizeof(int), cols, fp) != (size_t)cols) {
            printf("Error reading data from file.\n");
            free(temp);
            free(data);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }

    free(temp);
    free(data);
    fclose(fp);

    return 0;
}



