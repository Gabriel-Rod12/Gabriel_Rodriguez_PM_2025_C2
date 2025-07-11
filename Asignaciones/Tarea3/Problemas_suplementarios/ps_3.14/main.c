#include <stdio.h>
#include <math.h>

int main() {
    double x, termino, seno = 0.0;
    int i = 1, signo = 1, contador = 0;
    double factorial;

    printf("Ingrese el valor de x (en radianes): ");
    scanf("%lf", &x);

    do {
        factorial = 1.0;
        for (int j = 1; j <= i; j++) {
            factorial *= j;
        }
        termino = pow(x, i) / factorial;

        seno += signo * termino;

        signo = -signo;

        i += 2;

        contador++;
    } while (fabs(termino) > 0.001);

    printf("\nEl valor aproximado de sen(%.2lf) es: %.6lf\n", x, seno);
    printf("Numero de terminos utilizados: %d\n", contador);

    return 0;
}
