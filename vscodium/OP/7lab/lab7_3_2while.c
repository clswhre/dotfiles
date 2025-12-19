#include <stdio.h>
#include <math.h>

int main(){
    float fx,b=1, x = 0.5;
    while (x<=b) {
        fx = pow(x,0.25); 
        printf("%lf\n",fx);
        x+=0.1;
    }
}
