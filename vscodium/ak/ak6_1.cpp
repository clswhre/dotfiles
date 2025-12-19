#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    short int a[N];
    short int c = 0, d = 0;
    printf("Sum of number < 0\n\n");
    int n         = N;
    short int res = 0;
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 61 - 30;
        printf("A[%d] = %hd\n", i, a[i]);
    }
    __asm
    {
		mov bx, 0  // <bx> = 0
		mov dx, 0  // <dx> = 0
		mov ecx, n  // <ecx> = n
		lea si, a  // завантаження зміщення масиву в
		cycle :  // цикл cycle
			lodsw  // завантажуємо слово з пам'яті,
			cmp ax, bx  // ax = 0
			jnl exit1  // ax != 0 => exit
			sub dx,ax
		exit1:  // цикл exit1
			LOOP cycle  // зменшує значення в регістрі <ecx> на 1,
		mov res, dx
    }
    if (res > 32767 || res < -32768) {
        printf("Overflow!\n");
    }
    else {
        printf("Result = %hd\n", res);
    }
    return 0;
}