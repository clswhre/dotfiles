#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#define N 5
int main() {
    int n         = N * N;
    short int res = 0, res_c = 0;
    short int a[N][N];
    printf("Sum of number < 0\n\n");
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 61 - 30;
            printf("%5hd ", a[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (a[i][j] < 0) {
                res_c -= a[i][j];
            }
        }
    }
    printf("Result C++ = %hd\n", res_c);
    __asm {
		mov bx, 0  // <bx> = 0
		mov dx, 0  // <dx> = 0
		mov ecx, n  // <ecx> = n
		lea si, a  // завантаження зміщення масиву в
		cycle :  // цикл cycle
                lodsw  // завантажуємо слово з пам'яті,
                cmp ax, bx  // ax = 0
                jnl exit1  // ax > 0 => exit
                sub dx,ax  // res -= a[i][j]
		exit1:  // цикл exit1
		    LOOP cycle  // зменшує значення в регістрі <ecx> на 1,
		mov res, dx
    }
    if (res > 32767 || res < -32768) {
        printf("Overflow!\n");
    }
    else {
        printf("Result ASM = %hd\n", res);
    }
    return 0;
}