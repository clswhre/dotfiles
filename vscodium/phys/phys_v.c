#include <stdio.h>
#include <math.h>

int main(){
    double g=9.8,l=1.03;
    double alpha[5],alpha_d[5],u[5];
    for (int i = 0; i<=4; i++) {
        printf("alpha %d ==>",i+1); scanf("%lf",&alpha[i]);
        alpha_d[i] = alpha[i]*3.1415/180;               //переведення в градуси
        u[i] = sqrt(g * l) * 2 * sin(alpha_d[i] / 2);   // u=2{g*l}*sin(a/2)
        printf("%d ==> %lf\n",i+1,u[i]);        
    };

    return 0;
}