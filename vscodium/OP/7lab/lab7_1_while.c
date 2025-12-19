#include <stdio.h>

int main() {
    int a, b, sum = 0;
    printf("a? =\t");
    scanf("%d", &a);
    printf("b? =\t");
    scanf("%d", &b);
    if (a > b) {
        printf("Число A повинно бути меншим за B!");
    } else {
        int i = a;
        while (i <= b) {
        sum += i;
        i++;
        }
        printf("%d", sum);
    };

    return 0;
}