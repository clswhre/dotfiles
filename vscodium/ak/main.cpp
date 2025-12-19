#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define N 10
int main()
{
	short int a[N];
	short int c = 0, d = 0;
	printf("c<=a[i]<=d\n\n");
	do
	{
		printf("Enter the values of the range [-32768...32767]:\n");
		printf("c = "); scanf_s("%hd", &c);
		printf("d = "); scanf_s("%hd", &d);
		if (c >= d)
		{
			printf("c can not be greater or equal d! Enter values again.\n\n");
		}
	} while (c >= d);
	int n = N;
	short int res = 0;
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 21 - 10; // елементи масиву від -10 до 10
		printf("A[%d] = %hd\n", i, a[i]);
	}
	__asm
	{
		mov bx, c // <bx> = c
		mov dx, d // <dx> = d
		mov ecx, n // <ecx> = n
		lea si, a // завантаження зміщення масиву в
		регістр SI(замінює shr ecx, 1 та shl ecx, 1)
		cycle : // цикл cycle
		lodsw // завантажуємо слово з пам'яті,
			на який вказує регістр SI
			cmp ax, bx // порівняння вмісту регістрві <ax> і <bx>
			jl exit1 // якщо менше - переходимо до циклу exit1
			16
			cmp ax, dx // порівняння вмісту регістрві <ax> і <dx>
			jg exit1 // якщо більше - переходимо до циклу exit1
			inc res // збільшуємо значення res на 1
			exit1 : // цикл exit1
		LOOP cycle // зменшує значення в регістрі <ecx> на 1,
			порівнює отримане значення з 0 і якщо не менше переходить до cycle
	}
	if (res > 32767 || res < -32768)
	{
		printf("Overflow!\n");
	}
	else
	{
		printf("Result = %hd\n", res);
	}
	_getch();
	return 0;
}