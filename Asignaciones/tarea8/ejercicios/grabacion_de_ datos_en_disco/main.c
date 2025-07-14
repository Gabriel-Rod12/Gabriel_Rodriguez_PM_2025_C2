#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "alumnos.bin"

typedef struct {
    char nombre[50];
    char matricula[15];
    float promedio;
}Alumno;

void guardarAlumno();
Alumno* cargarAlumnos(int *n);
void mostrarAlumnos(Alumno *alumnos, int n);

int main()
{
    int opcion;
    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Agregar alumno\n");
        printf("2. Mostrar alumnos\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        if(opcion == 1)
        {
            guardarAlumno();
        }else if(opcion == 2)
        {
            int cantidad = 0;
            Alumno *alumnos = cargarAlumnos(&cantidad);
            if (alumnos != NULL && cantidad > 0)
            {
                mostrarAlumnos(alumnos, cantidad);
                free(alumnos);
            }else
            {
                printf("No hay alumnos registrados.\n");
            }
        }
    }while (opcion != 3);
    return 0;
}

void guardarAlumno()
{
    FILE *f = fopen(FILE_NAME, "ab");
    if (!f)
    {
        perror("No se pudo abrir el archivo");
        return;
    }

    Alumno *nuevo = (Alumno *)malloc(sizeof(Alumno));
    if (!nuevo)
    {
        printf("No se pudo asignar memoria.\n");
        fclose(f);
        return;
    }

    printf("\n--- Agregar Alumno ---\n");
    printf("Nombre: ");
    fflush(stdin);
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    printf("Matricula: ");
    fflush(stdin);
    fgets(nuevo->matricula, sizeof(nuevo->matricula), stdin);
    nuevo->matricula[strcspn(nuevo->matricula, "\n")] = '\0';

    printf("Promedio: ");
    scanf("%f", &nuevo->promedio);

    fwrite(nuevo, sizeof(Alumno), 1, f);
    fclose(f);
    free(nuevo);

    printf("Alumno guardado con exito.\n");
}

Alumno* cargarAlumnos(int *n)
{
    FILE *f = fopen(FILE_NAME, "rb");
    if(!f)
    {
        *n = 0;
        return NULL;
    }

    Alumno *alumnos = NULL;
    int count = 0;

    while (1)
    {
        Alumno temp;
        if(fread(&temp, sizeof(Alumno), 1, f) != 1)
            break;

        Alumno *aux = (Alumno *)realloc(alumnos, (count + 1) * sizeof(Alumno));
        if(!aux)
        {
            printf("No se pudo reasignar memoria.\n");
            free(alumnos);
            fclose(f);
            *n = 0;
            return NULL;
        }

        alumnos = aux;
        alumnos[count] = temp;
        count++;
    }

    fclose(f);
    *n = count;
    return alumnos;
}

void mostrarAlumnos(Alumno *alumnos, int n)
{
    printf("\n%-20s %-15s %-10s\n", "Nombre", "Matricula", "Promedio");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        Alumno *a = &alumnos[i];
        printf("%-20s %-15s %-10.2f\n", a->nombre, a->matricula, a->promedio);
    }
}
