//kp4-10
#include <stdio.h>
#include <math.h>
#include <float.h>
long double var10(long double x){
    return (2.0 * x * sin(x) - cos(x));
}
long double var10_pr1(long double x){
    return ( 2.0 * sin(x) + 2.0 * x * cos(x) + sin(x));
}
long double var10_pr2(long double x){
    return (-2.0 * x * sin(x) + 5 * cos(x) );
}
int check_convergence(long double a, long double b){
    long double step = (b - a) / 10000;
    for (long double x = a; x <= b; x += step){
        if (fabsl(var10(x) * var10_pr2(x)) < var10_pr1(x) * var10_pr1(x)){
           return 0;
        }
    }
    return 1;
}
long double find_x(long double x0, long double x){
    while (fabsl(x - x0) >= LDBL_EPSILON){
        printf("%Lf %Lf", x0, x);
        x0 = x;
        x = x0 - var10(x0) / var10_pr1(x0);
    }
    return x;
}
int main() {
    long double a = 0.4;
    long double b = 1;
    long double x0 = (a + b) / 2;
    long double x= x0 - var10(x0) / var10_pr1(x0);
    printf("\nNewton method\n");
    if (check_convergence(a, b) == 1){
        printf("Method is convergent\n");
        printf("x = %Lf", find_x(x0, x));
        printf("The value of the function for such x: %Lf", var10(x));
    }
    else{
        printf("Method doesn't convergent\n");
    }
    return 0;
}
