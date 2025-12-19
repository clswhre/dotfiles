#include <math.h>
#include <stdio.h>

int main(){
    float a=1,b=5,fx=0;
    float x=a;
    while (x<=b){
        fx=sin(x)*cos(pow(x, 2));
        printf("F(%.2lf) = %lf\n",x,fx);
        x++;
    }
    return 0;
}

