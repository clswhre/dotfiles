#include <math.h>
#include <stdio.h>

int main() { 
    float fx;
    float b=1;
    for (float x = 0.5; x<=b; x+=0.1) {
        fx = pow(x,0.25); 
        printf("%lf\n",fx);
    }
    return 0;
}
