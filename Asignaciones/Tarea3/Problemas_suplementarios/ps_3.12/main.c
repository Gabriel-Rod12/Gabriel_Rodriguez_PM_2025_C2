#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>

int main() {
    int NUM, i, j, div;

    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &NUM);

    printf("Numeros primos menores que %d:\n", NUM);

    for (i = 2; i < NUM; i++) {
        div = 0;
        for (j = 1; j <= i; j++) {
            if (i % j == 0) {
                div++;
            }
        }
        if (div == 2) {
            printf("%d ", i);
        }
    }
    return 0;
}
