#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 8 
#define COLS 7 

void print_matrix(int A[ROWS][COLS]) {
    int last_col = COLS - 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j == last_col && i % 2 == 0) {
                printf("[%3d] ", A[i][j]);
            } else {
                printf(" %3d  ", A[i][j]);
            }
        }
        printf("\n");
    }
}

void bubble_sort_flag_inplace(int A[ROWS][COLS], int* comparisons, int* swaps) {
    *comparisons = 0;
    *swaps = 0;
    int last_col = COLS - 1;

    int max_idx = (ROWS - 1) % 2 == 0 ? (ROWS - 1) : (ROWS - 2);
    int elements_count = (max_idx / 2) + 1;

    for (int pass = 0; pass < elements_count - 1; pass++) {
        bool swapped = false;

        for (int i = 0; i < max_idx - (pass * 2); i += 2) {
            (*comparisons)++;
            
            if (A[i][last_col] < A[i + 2][last_col]) {
                int temp = A[i][last_col];
                A[i][last_col] = A[i + 2][last_col];
                A[i + 2][last_col] = temp;
                
                (*swaps)++;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

void fill_background(int A[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {
            A[i][j] = 10 + (i + j) % 20;
        }
        if (i % 2 != 0) {
            A[i][COLS - 1] = 99;
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int A[ROWS][COLS];
    int last_col = COLS - 1;
    int comps = 0, swaps = 0;

    printf("=== Lab 5: Bubble Sort with Flag (Variant 16) ===\n");
    printf("Target: Last column, odd positions (marked in [brackets]), non-increasing order.\n\n");

    fill_background(A);
    A[0][last_col] = 80;
    A[2][last_col] = 60;
    A[4][last_col] = 40;
    A[6][last_col] = 20;

    printf("--- CASE 1: ALREADY SORTED (80, 60, 40, 20) ---\n");
    printf("Before sorting:\n");
    print_matrix(A);
    bubble_sort_flag_inplace(A, &comps, &swaps);
    printf("\nAfter sorting:\n");
    print_matrix(A);
    printf("Stats -> Comparisons: %d | Swaps: %d\n\n", comps, swaps);

    fill_background(A);
    for (int i = 0; i < ROWS; i += 2) {
        A[i][last_col] = rand() % 90 + 10;
    }

    printf("--- CASE 2: RANDOM UNSORTED ---\n");
    printf("Before sorting:\n");
    print_matrix(A);
    bubble_sort_flag_inplace(A, &comps, &swaps);
    printf("\nAfter sorting:\n");
    print_matrix(A);
    printf("Stats -> Comparisons: %d | Swaps: %d\n\n", comps, swaps);

    fill_background(A);
    A[0][last_col] = 20;
    A[2][last_col] = 40;
    A[4][last_col] = 60;
    A[6][last_col] = 80;

    printf("--- CASE 3: REVERSE SORTED (20, 40, 60, 80) ---\n");
    printf("Before sorting:\n");
    print_matrix(A);
    bubble_sort_flag_inplace(A, &comps, &swaps);
    printf("\nAfter sorting:\n");
    print_matrix(A);
    printf("Stats -> Comparisons: %d | Swaps: %d\n", comps, swaps);

    return 0;
}