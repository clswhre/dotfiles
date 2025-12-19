#include <iostream>
#include <stdio.h>
#include <cstdlib>
int main() {

    int a, b, c, result,one = 1;
    printf("a = "); scanf_s("%d", &a);
    printf("b = "); scanf_s("%d", &b);
    printf("c = "); scanf_s("%d", &c);
    // ( 9*b - 2 - c) / ( a*3 + b/c )
    __asm {
        mov eax, 9           // eax = 9
        //mov ebx, b            // ebx = b
        imul b             // edx:eax = 9 * b
        idiv one

        sub eax, 2            // eax = eax - 2
        mov ebx, c            // ebx = c
        sub eax, ebx          // eax = eax - ebx
        mov esi, eax          // esi = eax
        // 1 duzhka ( 9*b - 2 - c)

        mov eax, 3            // eax = 3
        mov ebx, a            // ebx = a
        imul ebx             // edx:eax = a * 3 

        mov ecx, 1            // ecx = 1
        idiv ecx             // eax = edx:eax / ecx

        mov ecx, b           // ecx = b
        xchg eax, ecx         // ecx <=> eax
        cdq                  // eax => edx:eax
        mov ebx, c            // ebx = c
        idiv ebx             // eax:edx / ebx = eax
        add eax, ecx          // a*3 + b/c
        // 2 duzhka

        xchg esi, eax        // 1duzhka <=> 2duzhka
        cdq                 // eax = edx:eax
        idiv esi            // eax:eax / esi = eax

        mov result, eax
    };

    printf("Result asm = %d\n", result);
}

        //mov bx, a           // bx = a
        //idiv bx             // eax/bx = ax = -15/a
        //mov bx, G           // bx = G = 25
        //add ax, bx          // -15/a + g

        //xchg ax, bx         // ax <=> bx
        //mov ax, a           // ax = a
        //cwd                 // ax => eax
        //mov cx, 4           // cx = 4
        //idiv cx             // eax/4 = ax

        //xchg ax, bx         // ax <=> bx
        //sub ax, bx          // ax = ax - bx = -15/a +25 - a/4
        //mov cx, e           // cx = e
        //sub ax, cx          // ax = ax - cx
        //// (-15 / a) + G - (a / 4) - e)

        //mov cx, ax

        //mov ax, b           // ax = b
        //imul a              // eax = ax * a = b * a
        //mov bx, 1            // bx = 1
        //idiv bx             // eax/bx = ax
        //dec ax              // ax = (b * a) - 1
        //sub ax, f           // ax = (b * a) - 1 - f
        //// ((b * a) - 1 - f)
        //xchg ax, cx         // ax <=> cx

        //cwd                 //  ax => dx:ax
        //idiv cx             //  dx:ax / cx
