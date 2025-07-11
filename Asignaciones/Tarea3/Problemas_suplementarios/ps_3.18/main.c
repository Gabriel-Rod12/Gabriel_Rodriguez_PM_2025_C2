#include <stdio.h>

int main() {
    int N, i, j;

    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N - i + 1; j++) {
            printf("%d ", j);
        }
        for (j = 1; j < i; j++) {
            printf("  ");
        }
        for (j = 1; j < i; j++) {
            printf("  ");
        }
        for (j = N - i + 1; j >= 1; j--) {
            printf("%d", j);
            if (j > 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
