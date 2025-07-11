#include <stdio.h>

int main() {
    int N1, N2, R;

    printf("Ingrese el primer numero: ");
    scanf("%d", &N1);
    printf("Ingrese el segundo numero: ");
    scanf("%d", &N2);

    while (N2 != 0) {
        R = N1 % N2;
        N1 = N2;
        N2 = R;
    }

    printf("El MCD es: %d\n", N1);

    return 0;
}
