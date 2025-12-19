#include <stdio.h>

int main() {
    int a, b, c;
    printf("Введіть сторони a, b, c:\t");
    scanf("%d%d%d", &a, &b, &c);

    if (a + b > c && b + c > a && a + c > b) {
        printf("Трикутник існує\n");

        int gyp, kat1, kat2;

        if (a >= b && a >= c) {
            gyp  = a;
            kat1 = b;
            kat2 = c;
        } else if (b >= a && b >= c) {
            gyp  = b;
            kat1 = a;
            kat2 = c;
        } else {
            gyp  = c;
            kat1 = a;
            kat2 = b;
        }

        if (kat1 * kat1 + kat2 * kat2 == gyp * gyp) {
            printf("Трикутник прямокутний\n");
        } else {
            printf("Трикутник НЕ прямокутний\n");
        }
    } else {
        printf("Трикутника не існує\n");
    }

    return 0;
}