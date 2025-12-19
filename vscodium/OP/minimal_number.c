#include <stdint.h>
#include <stdio.h>
int main() {

    int user_input;
    printf("Визначення мінімального число серед позитивних\n");
    do {
        int min,num,n=1;
        int first = 1;
        printf("\nВводьте додатні числа\n");
        printf("Для завершення введення введіть 0\n");

        while (1) {
            printf("Число %d --> ",n);
            scanf("%d", &num);
            if (num == 0) {
                break;
            }
            if (first) {
                min = num;
                first = 0;
            } else if (num < min) {
                min = num;
            }
            n++;
        }
        if (first) {
            printf("Не введено жодного додатного числа\n");
        } else {
            printf("\nМінімальне число - %d\n", min);
        }
        printf("\n1-Продовжити\n2-Завершити\n");
        printf(">>> ");
        scanf("%d", &user_input);
    } while (user_input == 1);
    return 0;
}
