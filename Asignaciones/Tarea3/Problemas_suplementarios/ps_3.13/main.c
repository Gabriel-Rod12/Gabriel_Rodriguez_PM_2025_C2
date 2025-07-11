#include <stdio.h>
#include <stdlib.h>

int main() {
    int N1, N2, i, j, div1, div2;

    printf("Ingrese el primer numero entero positivo: ");
    scanf("%d", &N1);
    printf("Ingrese el segundo numero entero positivo: ");
    scanf("%d", &N2);

    if (N1 > N2) {
        int temp = N1;
        N1 = N2;
        N2 = temp;
    }

    printf("Primos gemelos entre %d y %d:\n", N1, N2);

    for (i = N1; i <= N2 - 2; i++) {
        div1 = 0;
        for (j = 1; j <= i; j++) {
            if (i % j == 0) {
                div1++;
            }
        }
        div2 = 0;
        for (j = 1; j <= i + 2; j++) {
            if ((i + 2) % j == 0) {
                div2++;
            }
        }
        if (div1 == 2 && div2 == 2) {
            printf("(%d, %d)\n", i, i + 2);
        }
    }

    return 0;
}
