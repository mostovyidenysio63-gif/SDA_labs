#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 7
#define COLS 8

int binary_search_leftmost_range(float row[], int size) {
    int left = 0;
    int right = size - 1;
    int found_index = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (row[mid] >= 0.0 && row[mid] <= 5.0) {
            found_index = mid; 
            right = mid - 1;   
        }
        else if (row[mid] < 0.0) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return found_index;
}

int main() {
    float A[ROWS][COLS] = {
        {20.5, 15.0, 10.2, 5.0,  5.0,  3.2,  1.0,  -2.5}, 
        {4.5,  3.0,  2.1,  0.5,  0.0,  -1.2, -3.0, -5.5}, 
        {45.0, 32.1, 24.0, 18.5, 12.0, 9.4,  4.0,  1.2 }, 
        {50.0, 40.0, 30.0, 20.0, 15.0, 12.5, 9.9,  6.1 }, 
        {-1.0, -2.0, -3.5, -4.0, -5.1, -6.0, -7.2, -8.0}, 
        {10.0, 8.5,  5.2,  2.5,  2.5,  2.5,  -0.5, -1.0}, 
        {3.0,  2.0,  1.0,  0.0,  -1.0, -2.0, -3.0, -4.0}  
    };

    printf("=== Binary Search (Algorithm #2) ===\n\n");
    printf("Matrix dimensions: %d rows x %d columns\n\n", ROWS, COLS);

    printf("Input Matrix (sorted by non-increasing in rows):\n");
    for (int i = 0; i < ROWS; i++) {
        printf("Row %d: [ ", i);
        for (int j = 0; j < COLS; j++) {
            printf("%5.1f ", A[i][j]);
        }
        printf("]\n");
    }
    printf("\n--------------------------------------------------\n");
    printf("Searching for elements in range [0.0, 5.0] per row:\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < ROWS; i++) {
        int result_col = binary_search_leftmost_range(A[i], COLS);

        if (result_col != -1) {
            printf("Row %d: FOUND element %5.1f at coordinates (%d, %d) [leftmost]\n", 
                   i, A[i][result_col], i, result_col);
        } else {
            printf("Row %d: NOT FOUND (No elements match the range [0, 5])\n", i);
        }
    }

    printf("\nSimulation completed successfully.\n");
    return 0;
}