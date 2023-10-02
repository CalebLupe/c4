#include <stdio.h>
#include <stdlib.h>

// Create a 2d array of integers, with the given number of rows and columns.
// Each element of the array is set to a random integer in the range [low, high].
int** create_2d_array(int rows, int cols, int low, int high);
void free_2d_array(int** array);

// The main function reads in the arguments and then calls create_2d_array to create a random 2D array. 
// The function then writes the array to a file.

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
    if (!data) {
        printf("Error creating 2D array.\n");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error opening file for writing.\n");
        free_2d_array(data);
        exit(EXIT_FAILURE);
    }

    fwrite(&rows, sizeof(int), 1, fp);
    fwrite(&cols, sizeof(int), 1, fp);

    for (int i = 0; i < rows; i++) {
        if (fwrite(data[i], sizeof(int), cols, fp) != (size_t)cols) {
            printf("Error writing data to file.\n");
            free_2d_array(data);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    free_2d_array(data);
    fclose(fp);

    return 0;
}

// This function creates a 2D array of integers with the given number of rows and columns. 
// The values of the array are random integers between low and high, inclusive. 
// The function returns a pointer to the array if successful, or NULL if memory allocation fails.

int** create_2d_array(int rows, int cols, int low, int high) {
    int* data = malloc(rows * cols * sizeof(int));
    int** array = malloc(rows * sizeof(int*));
    if (!data || !array) {
        free(data);
        free(array);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        array[i] = data + i * cols;
    }

    srand(0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = low + rand() % (high - low + 1);
        }
    }

    return array;
}

// This function frees the memory allocated for a 2D array of integers.
void free_2d_array(int** array) {
    if (array) {
        free(array[0]);
        free(array);
    }
}
