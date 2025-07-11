#include <stdio.h>
#include <stdlib.h>

/*Escribe un diagrama de flujo y el correspondiente programa en C que realice lo
siguiente:

a. Calcule el monto correspondiente de cada venta.
b. Obtenga el número de boletos vendidos para cada una de las localidades.
c. Obtenga la recaudación total. */

int main()
{
    float L1, L2, L3, L4, L5, L6;
    int CLAi, CANi;
    int total1 = 0, total2 = 0, total3 = 0, total4 = 0, total5 = 0, total6 = 0;
    float monto = 0, total = 0;

    printf("Ingresa el precio de las 6 localidades: ");
    scanf("%f %f %f %f %f %f", &L1, &L2, &L3, &L4, &L5, &L6);

    printf("\nIngrese la localidad y la cantidad de boletos vendidos (Escriba 0 0 para terminar): ");
    scanf("%i %i", &CLAi, &CANi);

    while (CLAi != 0 || CANi != 0){
        switch(CLAi){
            case 1: monto = L1 * CANi; total1 += CANi;
                break;
            case 2: monto = L2 * CANi; total2 += CANi;
                break;
            case 3: monto = L3 * CANi; total3 += CANi;
                break;
            case 4: monto = L4 * CANi; total4 += CANi;
                break;
            case 5: monto = L5 * CANi; total5 += CANi;
                break;
            case 6: monto = L6 * CANi; total6 += CANi;
                break;\
            default: printf("Localidad no valida.\n"); monto = 0;
        }

        printf("Monto de la venta: $%.2f\n", monto);
        total = total + monto;

        // Leer siguiente venta
        printf("\nEscriba la siguiente venta: ");
        scanf("%i %i", &CLAi, &CANi);
    }

    printf("\nResumen:\n");
    printf("Localidad 1: %i boletos\n", total1);
    printf("Localidad 2: %i boletos\n", total2);
    printf("Localidad 3: %i boletos\n", total3);
    printf("Localidad 4: %i boletos\n", total4);
    printf("Localidad 5: %i boletos\n", total5);
    printf("Localidad 6: %i boletos\n", total6);
    printf("Recaudacion total: $%.2f\n", total);

    return 0;
}
