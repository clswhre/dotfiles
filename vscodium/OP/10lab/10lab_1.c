#include <math.h>
#include <stdio.h>

int main(){
    int n = 0,num=0;
    while (num<100) {
        n++;
        num = pow(2,n);
    };
    printf("Порядковий номер елементу n (2^n > 100) => %d", n);
    return 0;
}