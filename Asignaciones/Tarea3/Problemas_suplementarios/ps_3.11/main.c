#include <stdio.h>
#include <stdlib.h>

/*En una bodega manejan información sobre las cantidades producidas
de cada tipo de vino en los últimos años. Escribe un diagrama de flujo y
el correspondiente programa en C que permita calcular lo siguiente:
a. El total producido de cada tipo de vino en los últimos años.
b. El total de la producción anual de los últimos años.
Datos: N, VIN1,1, VIN1,2, VIN1,3, VIN1,4
VIN2,1, VIN2,2, VIN2,3, VIN2,4
. . .
VINN,1, VINN,2, VINN,3, VINN,4
Donde: N es una variable de tipo entero que representa el número de años.
VINi,j es una variable de tipo real que representa la cantidad de litros de
vino en el año i del tipo j (1≤ i ≤ N, 1≤ j ≤ 4). */

int main() {
    int N, i, j;
    int tipos = 4;
    float vino, totalTipo1 = 0, totalTipo2 = 0, totalTipo3 = 0, totalTipo4 = 0;
    float totalAnio, totalGeneral = 0;

    printf("Ingrese el numero de anios: ");
    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        totalAnio = 0;
        printf("Anio %d:\n", i);
        for (j = 1; j <= tipos; j++) {
            printf("  Tipo de vino %d (litros): ", j);
            scanf("%f", &vino);
            totalAnio += vino;
            if (j == 1) totalTipo1 += vino;
            else if (j == 2) totalTipo2 += vino;
            else if (j == 3) totalTipo3 += vino;
            else if (j == 4) totalTipo4 += vino;
        }
        printf("  Total producido en el anio %d: %.2f litros\n", i, totalAnio);
        totalGeneral += totalAnio;
    }

    // Mostrar total por tipo de vino
    printf("\nTotal producido por tipo de vino:\n");
    printf("  Tipo 1: %.2f litros\n", totalTipo1);
    printf("  Tipo 2: %.2f litros\n", totalTipo2);
    printf("  Tipo 3: %.2f litros\n", totalTipo3);
    printf("  Tipo 4: %.2f litros\n", totalTipo4);

    // Mostrar total general
    printf("\nTotal general producido en todos los anios: %.2f litros\n", totalGeneral);

    return 0;
}
