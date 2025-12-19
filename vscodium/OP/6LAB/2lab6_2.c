#include <stdio.h>

int main(){
    int goals_Dynamo, goals_Shakhtar;
    printf("Введіть кількість голів 'Динамо':\n");
    scanf("%d",&goals_Dynamo);
    printf("Введіть кількість голів 'Шахтар':\n");
    scanf("%d",&goals_Shakhtar);
    if (goals_Dynamo == goals_Shakhtar){
        printf("Нічия");
    }else {
    printf("%s", goals_Dynamo>goals_Shakhtar?"Перемога 'Динамо' ":"Перемога 'Шахтар'");
    }
    return 0;
}