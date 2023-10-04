#include "utilities.h"

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

void free_2d_array(int** array) {
    if (array) {
        free(array[0]);
        free(array);
    }
}

void print_2d_memory(int **data, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}

int** read_2d_array_from_file(const char* filename, int* rows, int* cols) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error opening file for reading.\n");
        exit(EXIT_FAILURE);
    }

    if (fread(rows, sizeof(int), 1, fp) != 1) {
        printf("Error reading rows from file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if (fread(cols, sizeof(int), 1, fp) != 1) {
        printf("Error reading cols from file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int** data = malloc(*rows * sizeof(int*));
    int* temp = malloc(*rows * *cols * sizeof(int));
    if (!data || !temp) {
        printf("Error allocating memory.\n");
        free(data);
        free(temp);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *rows; i++) {
        data[i] = temp + i * *cols;
        if (fread(data[i], sizeof(int), *cols, fp) != (size_t)*cols) {
            printf("Error reading data from file.\n");
            free(temp);
            free(data);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
    return data;
}

void write_2d_array_to_file(int** data, int rows, int cols, const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }

    if (fwrite(&rows, sizeof(int), 1, fp) != 1) {
        printf("Error writing rows to file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if (fwrite(&cols, sizeof(int), 1, fp) != 1) {
        printf("Error writing cols to file.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        if (fwrite(data[i], sizeof(int), cols, fp) != (size_t)cols) {
            printf("Error writing data to file.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);
}

int** add_2d_arrays(int** array1, int** array2, int rows, int cols) {
    int* data = malloc(rows * cols * sizeof(int));
    int** result = malloc(rows * sizeof(int*));
    if (!data || !result) {
        free(data);
        free(result);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        result[i] = data + i * cols;
        for (int j = 0; j < cols; j++) {
            result[i][j] = array1[i][j] + array2[i][j];
        }
    }

    return result;
}
