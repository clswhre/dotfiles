#include <stdio.h>
#include <iostream>

int main() {
    char a, b, x_asm, x_c;
    char g = 25, n = 12;
    char one = 1;
    printf("a (-128 .. 127): ");
    scanf_s("%hhd", &a);

    printf(" b (-128 .. 127): ");
    scanf_s("%hhd", &b);

    if (a > b) {
        x_c = a * b + 2;
    }
    else if (a == b) {
        x_c = g - n;
    }
    else {
        if (a != 0)
            x_c = (b * b - 9) / a;
        else
            x_c = 0;
    }

    if (b == 0 || a > 127 || a < -128 || b > 127 || b < -128)
    {
        printf("Помилка: ");
    }
    else if (a > b)
    {

        if ((a * b + 2) < -128 || (a * b + 2)  > 127)
        {
            printf("Помилка: ");
        }
        else
        {
            x_c = (a * b) + (a / b);
            printf("Результат на С++ X = % d\n", x_c);
        }
    }
    else if(a == b)
    {

        if ((a / b) + 9 < -128 || (a / b) + 9 > 127)
        {
            printf("Помилка: ");
        }
        else
        {
            x_c = (b * b - 9) / a;
            printf("С++ X = %d\n", x_c);
        }
    }

    __asm {
        mov al, a
        mov bl, b
        cmp al, bl

        jg greater
        je equal
        jl less 

        greater:
            imul b            // <al> = a, <ax> = a * b
            idiv one          // <al> = <ah> / 1
            add al, 2         // <al> = <al> - 2
            mov x_asm, al     // <al> => x_asm
            jmp exit_asm

        equal:
            mov al, g         // <al> = g
            sub al, n         // <al> = g - n
            mov x_asm, al     // <al> => x_asm
            jmp exit_asm

        less:
            xchg al,bl        // <al> <=> <bl>
            imul al           // <ax> = <al> * <al>
            idiv one          // <al> = <ax> / 1
            sub al, 9         // <al> = b^2 - 9
            cbw
            idiv bl           // 
            mov x_asm, al
            jmp exit_asm

            exit_asm :
    }

    printf("\nresult Assembler:    %hd\n", x_asm);
    printf("result C:  %hd\n", x_c);

    system("pause");
    return 0;
}