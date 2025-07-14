#include <stdio.h>

/* Alumnos.
El programa lee bloques variables de tipo estructura alumno de un archivo de acceso directo. */

typedef struct{ /* Declaracion de la estructura alumno. */
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void lee(FILE *); /* Prototipo de funcion. */

void main(void)
{

    FILE *ar;
    if((ar = fopen ("ad1.dat", "r")) != NULL)
        write(ar);
    else
        printf("\nEl archivo no se puede abrir");
    fclose(ar);
}

void lee(FILE *ap)
/* Esta funcion se utiliza para leer bloques de un archivo de acceso directo. */
{
    alumno alu;
    fread(&alu, sizeof(alumno), 1, ap);
    /* Observa que la funcin fread tiene los mismos argumentos que la funcion fwrite del programa anterior. Tambin es importante tomar nota de que cuando
    tenemos que leer los registros de un archivo utilizando una estructura repetitiva como el while, debemos realizar una primera lectura antes de
    ingresar al ciclo y luego las siguientes dentro del ciclo, pero como ltima instruccin del mismo. Esto se debe a que la lgica que siguen las
    instrucciones fwrite y fread es moverse y leer o escribir, segn sea el caso. Si no lo hiciramos de esta forma, terminaramos escribiendo la informacin
    del ultimo registro dos veces. Vamos a realizar un ejemplo sencillo para comprobar esto. */

    while (!feof(ap))
    {

        printf("\nMatrcula: %d", alu.matricula);
        printf("\tCarrera: %d", alu.carrera);
        printf("\tPromedio: %f\t ", alu.promedio);
        puts(alu.nombre);
        fread(&alu, sizeof(alumno), 1, ap);
    }
}
