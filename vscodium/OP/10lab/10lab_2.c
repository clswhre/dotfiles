#include <stdio.h>
int main() {
  int user_input;
  do {
    int j = 1, a1 = 1;
    for (int i = 1; i<=7; i+=2) {
        for (int j = i; j < 5+i; j++) {
            printf("%d ",j);
        }
        printf("\n");
    }
    printf("\n1 – продовжити роботу\n2 – завершити роботу\n");
    scanf("%d",&user_input);

  }while (user_input !=2 );
  return 0;
}
