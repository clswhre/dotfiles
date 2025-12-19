#include <stdio.h>
#include <math.h>

int main(){
    double E, y, m, l=795, d=8, g = 9.80665;
    double pi = 3.1415926535897932384626433;
    d = d / 1000;
    l = l / 1000;

    for (int i =1; i<=3; i++) {
        printf("m (в г)-->    ");
        scanf("%lf", &m);
        m = m / 1000;

        printf("y (в мм)-->    ");
        scanf("%lf",&y);
        y = y / 1000;


        double top,bottom;

        top = 64*m*g* pow(l,3);
        bottom = 3*pi*y*pow(d,4);
        E = ((top / bottom)) / pow(10, 9);

        printf("E%d = %.4lf ГПа\n",i,E);
    }


    return 0;
}