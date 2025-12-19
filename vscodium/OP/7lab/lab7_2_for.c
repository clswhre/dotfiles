#include <stdio.h>
#include <math.h>

int main() {
    int x, m;
    double bottom = 1, top, result;

    printf("Введіть m:\t");
    scanf("%d", &m);
    if (m < 0) {
        printf("Введіть число > 0\n");
        return 1;
    }else {
    
    printf("Введіть x:\t");
    scanf("%d", &x);
    
    for (int i = 1; i <= (2 * m - 1); ++i) {
        bottom *= i;
    }

    top = pow(x, 2 * m - 1);
    result = top / bottom;

    printf("Результат: %.6lf\n", result);
    }
    return 0;
}