#include <stdio.h>

/* Prueba de variables globales, locales y estáticas.
El programa utiliza funciones en las que se usan diferentes tipos de
➥ variables. */

int f1(void);
int f2(void);
int f3(void); /* Prototipos de funciones. */
int f4(void);
int K_global = 3; /* Variable global. */

void main(void)
{
    int I;
    for (I = 1; I <= 3; I++)
    {
        printf("\nEl resultado de la función f1 es: %d", f1());
        printf("\nEl resultado de la función f2 es: %d", f2());
        printf("\nEl resultado de la función f3 es: %d", f3());
        printf("\nEl resultado de la función f4 es: %d", f4());
    }
}
int f1(void)
/* La función f1 utiliza la variable global. */
{
K_global += K_global;
return (K_global);
}
int f2(void)
/* La función f2 utiliza la variable local. */
{
int K_local = 1;
K_local++;
return (K_local);
}
int f3(void)
/* La función f3 utiliza la variable estática. */
{
static int K = 8;
K += 2;
return (K);
}
int f4(void)
/* La función f4 utiliza dos variables con el mismo nombre: local
y global. */
{
int K_local = 5;
K_local = K_local + K_global; /* Uso de la variable local (K) y global (::K) */
return (K_local);
}
