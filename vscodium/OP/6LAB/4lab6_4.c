#include <stdio.h>

int main(){
    float x,y,fx;
    float r =5;
    scanf("%f%f",&x,&y);
    fx= x*x+y*y;
    printf("%s", (y>0 && fx<=r*r) ?"Точка належить області":"Точка не належить області");
    return 0;
}