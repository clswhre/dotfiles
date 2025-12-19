#include <stdio.h>

int main() {
  int user_input;
  printf("Визначення мінімального число серед позитивних\n");
  printf("Для завершення введення введіть нуль.\n");
    do {
        int min,first=1;
        for(int i=1,n=1;i!=0;){
            printf("Число %d --> ",n);
            scanf("%d", &i);
            if (i<=0){
                break;
            }
            if (first){
                min=i;
                first=0;
            }else if (i<min) {
                min = i;
            }
            n++;
        }
        if (first){
            printf("Не введено додатніх чисел\n");
        }else{
            printf("\nМінімальне число - %d\n",min);
        }
        printf("\n1-Продовжити\n2-Завершити\n");
        printf(">>>   ");
        scanf("%d", &user_input);
        if (user_input==2) {
            break;
        }
    } while (user_input != 0);
    return 0;
}
