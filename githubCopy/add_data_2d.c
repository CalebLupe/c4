#include <stdio.h>
#include <stdlib.h>

// Reads a 2D array from a file.
// The first two bytes of the file contain the number of rows and columns of the array.
// The remaining bytes of the file contain the array elements in row-major order.
// Returns a pointer to the array if successful, or NULL if memory allocation fails.

int** read_data_from_file(const char* filename, int* rows, int* cols);
void free_2d_array(int** array);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./add_data_2d <in file1> <in file2> <out filename>\n");
        exit(EXIT_FAILURE);
    }

    int rows1, cols1, rows2, cols2;
    int** data1 = read_data_from_file(argv[1], &rows1, &cols1);
    int** data2 = read_data_from_file(argv[2], &rows2, &cols2);

    if (!data1 || !data2) {
        printf("Error reading data from files.\n");
        free_2d_array(data1);
        free_2d_array(data2);
        exit(EXIT_FAILURE);
    }

    if (rows1 != rows2 || cols1 != cols2) {
        printf("Matrix dimensions do not match.\n");
        free_2d_array(data1);
        free_2d_array(data2);
        exit(EXIT_FAILURE);
    }

    int** result = malloc(rows1 * sizeof(int*));
    int* temp = malloc(rows1 * cols1 * sizeof(int));
    if (!result || !temp) {
        printf("Error allocating memory for result.\n");
        free_2d_array(data1);
        free_2d_array(data2);
        free(result);
        free(temp);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows1; i++) {
        result[i] = temp + i * cols1;
        for (int j = 0; j < cols1; j++) {
            result[i][j] = data1[i][j] + data2[i][j];
        }
    }

    FILE* fp = fopen(argv[3], "wb");
    if (!fp) {
        printf("Error opening output file for writing.\n");
        free_2d_array(data1);
        free_2d_array(data2);
        free_2d_array(result);
        exit(EXIT_FAILURE);
    }

    fwrite(&rows1, sizeof(int), 1, fp);
    fwrite(&cols1, sizeof(int), 1, fp);

    for (int i = 0; i < rows1; i++) {
        if (fwrite(result[i], sizeof(int), cols1, fp) != (size_t)cols1) {
            printf("Error writing result to file.\n");
            free_2d_array(data1);
            free_2d_array(data2);
            free_2d_array(result);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    free_2d_array(data1);
    free_2d_array(data2);
    free_2d_array(result);
    fclose(fp);

    return 0;
}

int** read_data_from_file(const char* filename, int* rows, int* cols) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        return NULL;
    }

    if (fread(rows, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return NULL;
    }
    if (fread(cols, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return NULL;
    }

    int** data = malloc(*rows * sizeof(int*));
    int* temp = malloc(*rows * *cols * sizeof(int));
    if (!data || !temp) {
        free(data);
        free(temp);
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *rows; i++) {
        data[i] = temp + i * *cols;
        if (fread(data[i], sizeof(int), *cols, fp) != (size_t)*cols) {
            free(temp);
            free(data);
            fclose(fp);
            return NULL;
        }
    }

    fclose(fp);
    return data;
}

void free_2d_array(int** array) {
    if (array) {
        free(array[0]);
        free(array);
    }
}
