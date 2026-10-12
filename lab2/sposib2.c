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
    double P2 = x;
    double current_sum = 0;
    long long op_count2 = 0;

    op_count2++; // ініціалізація x
    op_count2++; // P2 = x
    op_count2++; // current_sum = 0

    op_count2++; // ініціалізація i = 1
    for (int i = 1; i <= n; i++) {
        op_count2++; // перевірка умови i <= n (true)

        current_sum += (2 * i - 1);
        op_count2 += 4; // *, -, +, =

        double term = 1.0 + (x * x) / (M_PI * M_PI * current_sum);
        op_count2 += 6; // x*x, PI*PI, *current_sum, /, +, =

        P2 *= term;
        op_count2 += 2; // *, =

        op_count2++; 
    }
    op_count2++; 

    printf("\n--- Method 2 (Dynamic Programming) ---\n");
    printf("Result P: %.7f\n", P2);
    printf("Operation count: %lld\n", op_count2);

    return 0;
}