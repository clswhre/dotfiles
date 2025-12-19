#include <math.h>
#include <stdio.h>

int main() {
  float a = 1, b = 5, fx = 0;
  for (float x = a; x <= 5; x++) {
    fx = sin(x) * cos(pow(x, 2));
    printf("F(%.2lf) = %lf\n", x, fx);
  }
  return 0;
}