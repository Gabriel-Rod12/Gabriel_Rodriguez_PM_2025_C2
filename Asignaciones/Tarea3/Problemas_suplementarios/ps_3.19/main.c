#include <stdio.h>

int main() {
    int N, i, j;

    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &N);

    for (i = 0; i <= N; i++) {
        for (j = 0; j < N - i; j++) {
            printf(" ");
        }
        for (j = i; j <= 2 * i; j++) {
            printf("%d", j % 10);
        }
        for (j = 2 * i - 1; j >= i; j--) {
            printf("%d", j % 10);
        }

        printf("\n");
    }

    return 0;
}
