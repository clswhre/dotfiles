#include <cstdio>
#include <cstdlib>
#include <Windows.h>

int main() {
    SetConsoleCP( 65001 );
    SetConsoleOutputCP( 65001 );
    int a, b, x_c, x_asm, er = 0, over = 0;
    int g = 25, one = 1;
    long long temp_res;
    printf( "Введіть значення в діапазоні [-2147483648...2147483647]:\n" );
    printf( "a = " ); scanf_s( "%d", &a );
    printf( "b = " ); scanf_s( "%d", &b );

    if ( b == 0 ) {
        printf( "Помилка: " );
    } else if ( a < 20 ) {
        temp_res = (long long) a * b;
        if ( temp_res > 2147483647 || temp_res < -2147483648 ) {
            printf( "Помилка: " );
        } else {
            temp_res = (long long) ( a / b );
            if ( temp_res > 2147483647 || temp_res < -2147483648 || ( a * b ) > 2147483647 || ( a * b ) > -214748364 ) {
                printf( "Помилка: " );
            } else {
                x_c = (int) ( a * b ) + ( a / b );
                printf( "C++; X: %d\n", x_c );
            }
        }
    } else {
        temp_res = (long long) ( a / b ) + 9;

        if ( temp_res > 2147483647 || temp_res < -2147483648 ) {
            printf( "Помилка: " );
        } else {
            x_c = (int) ( temp_res / g );
            printf( "C++; X: %d\n", x_c );
        }
    }

    __asm{
        mov eax, a          // <eax> = a
        mov ebx, b          // <ebx> = b
        cmp b, 0            // b ? 0
        je zero             // b == 0 => zero

        cmp eax, 20         // a ? 20
        jl less             // a < 20 => less

        cdq                 // a = <edx:eax>
        idiv b              // <eax> = a / b
        add eax, 9          // <eax> = (a / b) + 9
        jo overflow         // OF = 1 ? => overflow
        cdq                 // <eax> = <edx:eax>
        idiv g              // <eax> = ((a / b) + 9 ) / g
        mov x_asm, eax      // x_asm <== eax
        jmp exit_asm        // exit

        less:
            cdq             // <eax> -> <edx:eax>
            idiv b          // <eax> = a / b
            mov ecx, a      // <ecx> = a
            xchg eax, ecx   // <eax> <=> <ecx>
            imul b          // <edx:eax> = a * b
            jo overflow
            idiv one        // <eax> = a * b
            add eax, ecx    // eax = (a * b) + (a / b)
            jo overflow     // OF = 1 ? ==> overflow
            mov x_asm, eax  // x_asm <== eax
            jmp exit_asm    // exit
        zero :
            mov er, 1
            jmp exit_asm
        overflow :
            mov over, 1
            jmp exit_asm
            exit_asm :
    }
    if ( er == 1 ) {
        printf( "ділення на 0!\n" );
    } else if ( over == 1 ) {
        printf( "переповення!\n" );
    } else if ( er == 0 && over == 0 ) {
        printf( "Assembler X = %d\n", x_asm );
    }
    system( "Pause" );
    return 0;
}