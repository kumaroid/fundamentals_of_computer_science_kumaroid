#include <stdio.h>
#include <math.h>

typedef long double ld;
typedef ld(*pFunc)(ld);

ld machineeps(){
    ld eps = 1;
    while(1 < 1 + eps)
        eps /= 2;
    return eps;
}

ld dx1(ld x){
    return expl(x) + 1 / (2 * sqrtl(1 + expl(2 * x))) * expl(2 * x) * 2;
}

ld dx2(ld x){
    return 2 * x * cos(x) + 3 * sin(x);
}

ld dx3(ld x){
    return 5*cos(x) - 2 * x * sin(x);
}

ld dx4(ld x){
    return expl(x) + 2*(expl(2*x)/sqrt(expl(2*x)+1)) - expl(4*x)/pow(expl(2*x)+1,1.5);    
}

ld sign(ld x){
    ld epsilon = machineeps();
    return x > epsilon ? 1.l : x < -epsilon ? -1.l : 0.l;
}

ld dichotomy1(pFunc f, ld a, ld b){
    ld epsilon = machineeps();
    ld x = (a + b) / 2;
    while (fabsl(a-b) > epsilon){
        x = (a + b) / 2;
        if(f(a) * f(x) > 0.l) a = x;
        else b = x;
    }
    return x;
}

ld iteration1(pFunc f, ld a, ld b){
    ld epsilon = machineeps();
    ld x = (a + b) / 2;
    while(fabsl(f(x)) > epsilon){
        x = x - f(x)*sign(dx1(x));
    }
    return x;
}

ld newton1(pFunc f, ld a, ld b){
    ld epsilon = machineeps();
    ld x = (a + b) / 2;
    if (fabs(f(x) * dx4(x)) >= (dx1(x) * dx1(x))){
        return NAN;
    }
    while(fabsl(f(x)/ dx1(x)) > epsilon){
        x = x - f(x)/dx1(x);
    }
    return x;
}

ld dichotomy2(pFunc f, ld a, ld b){
    ld epsilon = machineeps();
    ld x = (a + b) / 2;
    while (fabsl(a-b) > epsilon){
        x = (a + b) / 2;
        if(f(a) * f(x) > 0.l) a = x;
        else b = x;
    }
    return x;
}

ld iteration2(pFunc f, ld a, ld b){
    ld epsilon = machineeps();
    ld x = (a + b) / 2;
    while(fabsl(f(x)) > epsilon){
        x = (x - f(x)*sign(dx2(x)));
    }
    return x;
}

ld newton2(pFunc f, ld a, ld b){
    ld epsilon = machineeps();
    ld x = (a + b) / 2;
    if (fabs(f(x) * dx3(x)) >= (dx2(x) * dx2(x))){
        return NAN;
    }
    while(fabsl(f(x)/ dx2(x)) > epsilon){
        x = x - f(x)/dx2(x);
    }
    return x;
}

ld func1(ld x){
    return expl(x) + sqrtl(1.l + expl(2 * x)) - 2.l;
}

ld func2(ld x){
    return 2*x*sin(x)- cos(x);
}

int main(){
    ld a1 = -1.l, b1 = 0.l;
    ld a2 = 0.l, b2 = 1.l;
    printf("dichotomy method result 11 variant: %Lf\n", dichotomy1(func1, a1, b1));
    printf("iteration method result 11 variant: %Lf\n", iteration1(func1, a1, b1));
    printf("newton method result 11 variant: %Lf\n", newton1(func1, a1, b1));
    printf("\n");
    printf("dichotomy method result 10 variant: %Lf\n", dichotomy2(func2, a2, b2));
    printf("iteration method result 10 variant: %Lf\n", iteration2(func2, a2, b2));
    printf("newton method result 10 variant: %Lf\n", newton2(func2, a2, b2));
}


