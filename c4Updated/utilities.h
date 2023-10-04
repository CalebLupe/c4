#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>

// Create a 2d array of integers, with the given number of rows and columns.
// Each element of the array is set to a random integer in the range [low, high].
int** create_2d_array(int rows, int cols, int low, int high);

// This function frees the memory allocated for a 2D array of integers.
void free_2d_array(int** array);

// This function prints the contents of a 2D array of integers.
void print_2d_memory(int **data, int rows, int cols);

// Function to read a 2D array from a binary file.
int** read_2d_array_from_file(const char* filename, int* rows, int* cols);

// Function to write a 2D array to a binary file.
void write_2d_array_to_file(int** data, int rows, int cols, const char* filename);

// Function to add two 2D arrays together.
int** add_2d_arrays(int** array1, int** array2, int rows, int cols);


#endif // UTILITIES_H