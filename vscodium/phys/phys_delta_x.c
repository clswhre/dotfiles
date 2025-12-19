#include <stdio.h>
#include <math.h>

int main() {
    double x1, x2, x3, x4, x5;
    double x1_abs, x2_abs, x3_abs, x4_abs, x5_abs;
    double x_, Sx, deltaX;
    double delta_x_random, delta_x_instrumental, delta_x_vidliku,d;
    int n = 5,inst;
    double t = 2.571;
    double t_p = 1.962;
    double p = 0.95;
    printf("x1-5:\t");
    scanf("%lf %lf %lf %lf %lf", &x1, &x2, &x3, &x4, &x5);
    printf("1-Штангенциркуль\n2-Ваги\n--> ");
    scanf("%d",&inst);
    switch (inst) {
    case 1:
        d = 0.1;
        break;
    case 2:
        d = 0.01;
        break;
    default:
      printf("Не правильний інструмент!");
      break;
      return 1;
    };


    x_ = (x1 + x2 + x3 + x4 + x5) / n;

    x1_abs = x1 - x_;
    x2_abs = x2 - x_;
    x3_abs = x3 - x_;
    x4_abs = x4 - x_;
    x5_abs = x5 - x_;

    Sx = sqrt((pow(x1_abs,2) + pow(x2_abs,2) + pow(x3_abs,2) + pow(x4_abs,2) + pow(x5_abs,2)) / (n*(n-1)));

    delta_x_random = t_p * Sx;
    delta_x_instrumental = (d * t_p)/ sqrt(3);
    delta_x_vidliku = p * (0.1 /2.0);
    deltaX = sqrt(pow(delta_x_random,2) + pow(delta_x_instrumental,2) + pow(delta_x_vidliku,2));

    printf("%.3lf\n%.3lf\n%.3lf\n%.3lf\n%.3lf\n",x1_abs,x2_abs,x3_abs,x4_abs,x5_abs);
    printf("Похибки: випадковa = %.3lf, інструментальна = %.3lf, та відліку = %.3lf\n", delta_x_random, delta_x_instrumental, delta_x_vidliku);
    printf("x = %.3lf ± %.3lf\n", x_, deltaX);
    return 0;
}
