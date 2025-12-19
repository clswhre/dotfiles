#include <stdio.h>
#include <math.h>

int main(){
    double a,b,c,disc,x1,x2;
    printf("Введіть a, b та c  квадратного рівняння: \t");
    scanf("%lf%lf%lf",&a,&b,&c);
    disc= pow(b,2) - 4*a*c;
    if (disc > 0){
        x1 = ((-b) - sqrt(disc)) / 2*a;
        x2 = ((-b) + sqrt(disc)) / 2*a;
        printf("2 розв'язки:\nx1=%.2lf, x2=%.2lf",x1,x2);
    }else if (disc == 0){
        x1 = -b / 2*a;
        printf("1 розв'язок:\nx1=%.2lf",x1);
    }else{
        printf("Розв'язків немає");
    }
    return 0;
}