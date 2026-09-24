#include <stdio.h>
#include <windows.h>

int main(void)
{
    double x;
    double y;
    int is_defined = 0;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Введіть значення x: ");
    scanf("%lf", &x);

    if (x >= 2 && x <= 7)
    {
        y = x * x * x + 14;
        is_defined = 1;
    }
    else if ((x > -13 && x <= -3) || x > 14)
    {
        y = -4 * x * x * x + 3 * x - 7;
        is_defined = 1;
    }

    if (is_defined == 1)
    {
        printf("y(x) = %.3f\n", y);
    }
    else
    {
        printf("Функція не визначена для заданого x.\n");
    }

    return 0;
}