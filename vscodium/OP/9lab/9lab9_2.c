#include <stdio.h>
int main() {
    int num, i = 0, remainder;

    printf("Введіть натуральне число (n > 9): ");
    scanf("%d", &num);
    if (num<=9) {
        printf("Введіть n > 9!");
        return 1;
    };
    int temp = num;
    while (temp > 0) {
        remainder = temp % 10;
        if (remainder == 1) {
            i++;
        };
        temp = temp / 10;
    }
    printf("Кількість одиниць у числі %d = %d", num, i);
    return 0;
}