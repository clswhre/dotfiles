#include <stdio.h>
int main() {
    int result;
    double x, y;
    
    printf(" x: ");
    scanf("%lf", &x);
    
    printf(" y: ");
    scanf("%lf", &y);
    
        if (x > 0) {
        if ( y>0 && y < (x + 1) && y > (-x + 1)) {
            result=1;
        } else {
            result=0;
        }
    } else if (x < 0) {
        if (y>0 && y > (x + 1) && y < (-x + 1)) {
            result=1;
        } else {
            result=0;
        }
    } else {
        result=0;
    };
    printf("%d",result);
    return 0;
}