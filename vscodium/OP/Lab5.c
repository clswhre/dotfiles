#include <locale.h>
#include <math.h>
#include <wchar.h>

int main() {   
    setlocale(LC_ALL, ""); 
    
    int option;
    
    wprintf(L"~~МЕНЮ~~\n");
    wprintf(L" 1 - Перше завдання\n");
    wprintf(L" 2 - Друге завдання\n");
    wprintf(L"Оберіть завдання: ");
    wscanf(L"%d", &option);
    
    if (option == 1) {
        wchar_t letter;
        wprintf(L"\nEnter an English letter: ");
        wscanf(L" %lc", &letter);
        
        switch(letter) {
            case L'A':
                wprintf(L"A - Antelope\n");
                break;
            case L'B':
                wprintf(L"B - Bear\n");
                break;
            case L'C':
                wprintf(L"C - Cat\n");
                break;
            case L'D':
                wprintf(L"D - Dolphin\n");
                break;
            case L'E':
                wprintf(L"E - Eagle\n");
                break;
            case L'F':
                wprintf(L"F - Fox\n");
                break;
            case L'G':
                wprintf(L"G - Giraffe\n");
                break;
            case L'H':
                wprintf(L"H - Horse\n");
                break;
            case L'I':
                wprintf(L"I - Iguana\n");
                break;
            case L'J':
                wprintf(L"J - Jaguar\n");
                break;
            case L'K':
                wprintf(L"K - Kangaroo\n");
                break;
            case L'L':
                wprintf(L"L - Lion\n");
                break;
            case L'M':
                wprintf(L"M - Monkey\n");
                break;
            case L'N':
                wprintf(L"N - Narwhal\n");
                break;
            case L'O':
                wprintf(L"O - Owl\n");
                break;
            case L'P':
                wprintf(L"P - Parrot\n");
                break;
            case L'Q':
                wprintf(L"Q - Quail\n");
                break;
            case L'R':
                wprintf(L"R - Rabbit\n");
                break;
            case L'S':
                wprintf(L"S - Snake\n");
                break;
            case L'T':
                wprintf(L"T - Tiger\n");
                break;
            case L'U':
                wprintf(L"U - Uakari\n");
                break;
            case L'V':
                wprintf(L"V - Vulture\n");
                break;
            case L'W':
                wprintf(L"W - Wolf\n");
                break;
            case L'X':
                wprintf(L"X - X-ray fish\n");
                break;
            case L'Y':
                wprintf(L"Y - Yak\n");
                break;
            case L'Z':
                wprintf(L"Z - Zebra\n");
                break;
            default:
                wprintf(L"НЕ англійська буква!\n");
        }
    } else if (option == 2) {
        int xb, func;
        double a, e = 2.71828, fx, x, y;
        
        wprintf(L"Введіть xb:\t");
        wscanf(L"%d", &xb);
        wprintf(L"x , y =\t");
        wscanf(L"%lf %lf", &x, &y);
        wprintf(L"Виберіть функцію:\n1 -- sin(x)\n2 -- x^2\n3 -- e^x\n~> ");
        wscanf(L"%d", &func);
        
        switch (func) {
            case 1:
                fx = sin(x);
                wprintf(L"f(x)=sin(x)\n");
                break;
            case 2:
                fx = pow(x, 2);
                wprintf(L"f(x)=x^2\n");
                break;
            case 3:
                fx = pow(e, x);
                wprintf(L"f(x)=e^x\n");
                break;
            default:
                wprintf(L"Невірне число!\n");
                return 1;
        }
        
        if (xb > 1 && 10 > xb) {
            a = pow(e, fx);
        } else if (xb > 12 && 40 > xb) {
            a = cbrt(fabs(fx + y));
        } else {
            a = y * fx * fx;
        }
        
        wprintf(L"a = %lf\n", a);
    } else {
        wprintf(L"Невірний вибір!\n");
    }

    return 0;
}