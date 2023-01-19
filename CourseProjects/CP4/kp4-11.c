#include <stdio.h>
#include <math.h>

typedef long double ld;
typedef ld(*pFunc)(ld);

const ld k = 1;

ld machineeps() {
    ld eps = 1;
    while(1 < 1 + eps)
        eps /= 2;
    return eps;
}
ld epsilon;

ld dx1(ld x){
    return expl(x) + 1 / (2 * sqrtl(1 + expl(2 * x))) * expl(2 * x) * 2;
}

ld dx2(ld x){
    return ((1 / x) - 1);
}

ld sign(ld x){
    return x > epsilon ? 1.l : x < -epsilon ? -1.l : 0.l;
}

ld dihotomy(pFunc f, ld a, ld b){
    ld x = (a + b) / 2;
    while (fabsl(a-b) > epsilon * k){
        x = (a + b) / 2;
        if(f(a) * f(x) > 0.l) a = x;
        else b = x;
    }
    return x;
}

ld iteration1(pFunc f, ld a, ld b){
    ld x = (a + b) / 2;
    while(fabsl(f(x)) > epsilon * k){
        x = x - f(x)*sign(dx1(x));
    }
    return x;
}

ld newton1(pFunc f, ld a, ld b){
    ld x = (a + b) / 2;
    while(fabsl(f(x)/ dx1(x)) > epsilon * k){
        x = x - f(x)/dx1(x);
    }
    return x;
}

ld iteration2(pFunc f, ld a, ld b){
    ld x = (a + b) / 2;
    while(fabsl(f(x)) > epsilon * k){
        x = x - f(x)*sign(dx2(x));
        printf("%Lf\n", x);
    }
    return x;
}

ld newton2(pFunc f, ld a, ld b){
    ld x = (a + b) / 2;
    while(fabsl(f(x)/ dx2(x)) > epsilon * k){
        x = x - f(x)/dx2(x);
    }
    return x;
}

ld a1 = -1.l, b1 = 0.l;
ld func1(ld x){
    return expl(x) + sqrtl(1.l + expl(2 * x)) - 2.l;
}

ld a2 = 2.l, b2 = 3.l;
ld func2(ld x){
    return logl(x) - x + 1.8l;
}



int main(){
    epsilon = machineeps();
    printf("dichotomy method result 11 variant: %Lf\n", dihotomy(func1, a1, b1));
    printf("iteration method result 11 variant: %Lf\n", iteration1(func1, a1, b1));
    printf("newton method result 11 variant: %Lf\n", newton1(func1, a1, b1));
    printf("\n");
}
