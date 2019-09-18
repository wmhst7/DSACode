#include <stdio.h>
int main()
{
    double a = 25.0 - 1e-8;
    double b = 200.0;
    printf("%lf %lf %lf\n", a, b, a * b);
}