#include <math.h>
#include <stdio.h>

int main(){
    double l,g,T,pi = 3.1415;
    for (int i=1; i<=5; i++) {
        printf("l (м) - ");
        scanf("%lf",&l);

        printf("T - ");
        scanf("%lf",&T);

        g = 4*pow(pi,2)*(l/pow(T,2));
        printf("%lf\n",g);

    }
    return 0;
}