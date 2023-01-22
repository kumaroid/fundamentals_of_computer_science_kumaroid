#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#define DBL_PI_2 1.5707963267948966192
#define MAX_ITER 20

typedef unsigned uint;
typedef float flt;
typedef double dbl;
typedef long double ldbl;
unsigned long int n = 1;
const double eps = 10e-16;

dbl sinSqrTaylor(dbl x);

void tabulation(dbl a, dbl b, uint n);

int main(){
    int n;
    scanf("%d", &n);
    tabulation(0.0, DBL_PI_2, n);
    return 0;
}

void tabulation(const dbl a, const dbl b, const uint n){
    const dbl delta = (b - a) / n;
    for (uint i = 0; i <= n; ++i){
        const dbl x = a + i * delta;
        printf("%.6lf %.15lf %.15lf\n", x, sin(x) * sin(x), sinSqrTaylor(x));
    }
}

dbl sinSqrTaylor(const dbl x) {
    dbl result = 0.0, member = -0.5;
    for (uint n = 1; n <= MAX_ITER; ++n) {
        member *= -4.0 * x * x / (2.0 * n - 1.0) / (2.0 * n);
        result += member;
    }
    return result;
}
