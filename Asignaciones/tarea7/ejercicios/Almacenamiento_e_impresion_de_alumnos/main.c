#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "alumnos.bin"

typedef struct
{
    char nombre[50];
    char matricula[15];
    float promedio;
}Alumno;

void agregarAlumno();
int cargarAlumnos(Alumno alumnos[]);
void guardarAlumnos(Alumno alumnos[], int n);
void ordenarPorNombre(Alumno alumnos[], int n);
void ordenarPorPromedio(Alumno alumnos[], int n);
void mostrarAlumnos(Alumno alumnos[], int n);
void menu();

int main()
{
    menu();
    return 0;
}

void agregarAlumno()
{
    FILE *f = fopen(FILE_NAME, "ab");  // Aadir al archivo
    if (!f)
    {
        perror("No se pudo abrir el archivo");
        return;
    }
    Alumno a;
    printf("\n--- Agregar Alumno ---\n");
    printf("Nombre: ");
    fflush(stdin);
    fgets(a.nombre, sizeof(a.nombre), stdin);
    a.nombre[strcspn(a.nombre, "\n")] = '\0';  // Eliminar salto de lnea

    printf("Matrcula: ");
    fflush(stdin);
    fgets(a.matricula, sizeof(a.matricula), stdin);
    a.matricula[strcspn(a.matricula, "\n")] = '\0';

    printf("Promedio: ");
    scanf("%f", &a.promedio);

    fwrite(&a, sizeof(Alumno), 1, f);
    fclose(f);

    printf("Alumno guardado correctamente.\n");
}

int cargarAlumnos(Alumno alumnos[])
{
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f)
    {
        return 0;
    }

    int i = 0;
    while (fread(&alumnos[i], sizeof(Alumno), 1, f) == 1 && i < MAX)
    {
        i++;
    }
    fclose(f);
    return i;
}

void ordenarPorNombre(Alumno alumnos[], int n)
{
    Alumno temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (strcmp(alumnos[j].nombre, alumnos[j+1].nombre) > 0)
            {
                temp = alumnos[j];
                alumnos[j] = alumnos[j+1];
                alumnos[j+1] = temp;
            }
        }
    }
}

void ordenarPorPromedio(Alumno alumnos[], int n)
{
    Alumno temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (alumnos[j].promedio < alumnos[j+1].promedio)
            {
                temp = alumnos[j];
                alumnos[j] = alumnos[j+1];
                alumnos[j+1] = temp;
            }
        }
    }
}

void mostrarAlumnos(Alumno alumnos[], int n)
{
    printf("\n%-20s %-15s %-10s\n", "Nombre", "Matrcula", "Promedio");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-20s %-15s %-10.2f\n", alumnos[i].nombre, alumnos[i].matricula, alumnos[i].promedio);
    }
}

void menu()
{
    Alumno alumnos[MAX];
    int opcion;

    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Agregar alumno\n");
        printf("2. Mostrar alumnos ordenados por nombre\n");
        printf("3. Mostrar alumnos ordenados por promedio\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion)
        {
            case 1: agregarAlumno();
                break;
            case 2:
            {
                int n = cargarAlumnos(alumnos);
                ordenarPorNombre(alumnos, n);
                mostrarAlumnos(alumnos, n);
                break;
            }
            case 3:
            {
                int n = cargarAlumnos(alumnos);
                ordenarPorPromedio(alumnos, n);
                mostrarAlumnos(alumnos, n);
                break;
            }
            case 4: printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invlida.\n");
        }
    }while (opcion != 4);
}
