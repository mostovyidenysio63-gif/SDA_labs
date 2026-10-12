#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    int n;
    printf("Input n: ");
    if (scanf("%d", &n) != 1) return 1;

    double x = 0.5;
    double P = x;
    long long op_count = 0;

    op_count++; // x = 0.5
    op_count++; // P = x

    op_count++; // i = 1
    for (int i = 1; i <= n; i++) {
        op_count++; // i <= n (true)

        double sum = 0;
        op_count++; // sum = 0

        op_count++; // j = 1
        for (int j = 1; j <= i; j++) {
            op_count++; // j <= i (true)

            sum += (2 * j - 1);
            op_count += 4; // * , - , + , =

            op_count++; // j++
        }
        op_count++; // j <= i (false)

        double term = 1.0 + (x * x) / (M_PI * M_PI * sum);
        op_count += 6; // x*x, PI*PI, *sum, /, +, =

        P *= term;
        op_count += 2; // * , =

        op_count++; // i++
    }
    op_count++; // i <= n (false)

    printf("\n--- Method 1 (Nested Loops) ---\n");
    printf("Result P: %.7f\n", P);
    printf("Operation count: %lld\n", op_count);

    return 0;
}