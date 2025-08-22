#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaracion de tope maximo de vehiculos en el programa y definicion de archivos para guardar los vehiculos y los datos generales(Combustibles) en el disco.
#define MAX_VEHICULOS 100
#define ARCHIVO_VEHICULOS "vehiculos.dat"
#define ARCHIVO_DATOS "datos_generales.dat"

//Estructura de datos para la plantilla de los vehiculos que seran agregados
typedef struct {
    char placa[20];
    char marca[50];
    char modelo[50];
    char tipo_combustible[10]; // "gasolina" o "gasoil"
    float km_por_galon_carretera;
    float km_por_galon_ciudad;
    float costo_gomas;
    int km_vida_gomas;
    float costo_seguro_anual;
    float costo_mantenimiento;
    int km_mantenimiento;
    float costo_vehiculo;
    int vida_util_anios;
    int km_promedio_anual;
} Vehiculo;
//Estructura para datos generales
typedef struct {
    float costo_gasolina;
    float costo_gasoil;
} DatosGenerales;

// Variables globales
Vehiculo vehiculos[MAX_VEHICULOS];
int totalVehiculos = 0;
DatosGenerales datosGenerales;

// ---------------- FUNCIONES DE ARCHIVO ----------------
void guardarVehiculos() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "wb");
    if (!f) { printf("Error al guardar vehculos.\n"); return; }
    fwrite(&totalVehiculos, sizeof(int), 1, f);
    fwrite(vehiculos, sizeof(Vehiculo), totalVehiculos, f);
    fclose(f);
}

void cargarVehiculos() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "rb");
    if (!f) return; // No existe el archivo
    fread(&totalVehiculos, sizeof(int), 1, f);
    if (totalVehiculos < 0 || totalVehiculos > MAX_VEHICULOS) {
        totalVehiculos = 0; // Proteccion basica
    } else {
        fread(vehiculos, sizeof(Vehiculo), totalVehiculos, f);
    }
    fclose(f);
}

void guardarDatosGenerales() {
    FILE *f = fopen(ARCHIVO_DATOS, "wb");
    if (!f) { printf("Error al guardar datos generales.\n"); return; }
    fwrite(&datosGenerales, sizeof(DatosGenerales), 1, f);
    fclose(f);
}

void cargarDatosGenerales() {
    FILE *f = fopen(ARCHIVO_DATOS, "rb");
    if (!f) {
        datosGenerales.costo_gasolina = 290.0f;
        datosGenerales.costo_gasoil   = 242.0f;
        guardarDatosGenerales();
        return;
    }
    fread(&datosGenerales, sizeof(DatosGenerales), 1, f);
    fclose(f);
}

//Lista de vehiculos
void listarVehiculos() {
    if (totalVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    for (int i = 0; i < totalVehiculos; i++) {
        printf("%d) %s - %s %s (%s)\n",
                i+1,
                vehiculos[i].placa,
                vehiculos[i].marca,
                vehiculos[i].modelo,
                vehiculos[i].tipo_combustible);
    }
}
// Creacion de vehiculos                    
void crearVehiculo() {
    if (totalVehiculos >= MAX_VEHICULOS) {
        printf("No se pueden agregar mas vehiculos.\n");
        return;
    }
    Vehiculo v;
    printf("Placa: "); scanf("%19s", v.placa);
    printf("Marca: "); scanf("%49s", v.marca);
    printf("Modelo: "); scanf("%49s", v.modelo);
    printf("Tipo de combustible (gasolina/gasoil): "); scanf("%9s", v.tipo_combustible);
    printf("Km por galon en carretera: "); scanf("%f", &v.km_por_galon_carretera);
    printf("Km por galon en ciudad: "); scanf("%f", &v.km_por_galon_ciudad);
    printf("Costo de gomas: "); scanf("%f", &v.costo_gomas);
    printf("Vida util de gomas (Km): "); scanf("%d", &v.km_vida_gomas);
    printf("Costo seguro anual: "); scanf("%f", &v.costo_seguro_anual);
    printf("Costo mantenimiento: "); scanf("%f", &v.costo_mantenimiento);
    printf("Km por mantenimiento: "); scanf("%d", &v.km_mantenimiento);
    printf("Costo del vehiculo: "); scanf("%f", &v.costo_vehiculo);
    printf("Vida util (anios): "); scanf("%d", &v.vida_util_anios);
    printf("Km promedio anual: "); scanf("%d", &v.km_promedio_anual);

    vehiculos[totalVehiculos++] = v;
    guardarVehiculos();
    printf("Vehiculo agregado correctamente.\n");
}
// Funcion para borrar vehiculos
void borrarVehiculo() {
    if (totalVehiculos == 0) {
        printf("No hay vehiculos para borrar.\n");
        return;
    }
    listarVehiculos();
    printf("Ingrese el numero del vehiculo a borrar (0 para cancelar): ");
    int idx; scanf("%d", &idx);

    if (idx == 0) {
        printf("Accion cancelada.\n");
        return;
    }
    if (idx < 1 || idx > totalVehiculos) {
        printf("Indice invalido.\n");
        return;
    }

    // Desplazar hacia la izquierda para sobrescribir el eliminado
    for (int i = idx - 1; i < totalVehiculos - 1; i++) {
        vehiculos[i] = vehiculos[i + 1];
    }
    totalVehiculos--;
    guardarVehiculos();
    printf("Vehiculo borrado correctamente.\n");
}

//Gestion de datos generales
void modificarDatosGenerales() {
    printf("Costo gasolina actual: %.2f\n", datosGenerales.costo_gasolina);
    printf("Nuevo costo gasolina: "); scanf("%f", &datosGenerales.costo_gasolina);
    printf("Costo gasoil actual: %.2f\n", datosGenerales.costo_gasoil);
    printf("Nuevo costo gasoil: "); scanf("%f", &datosGenerales.costo_gasoil);
    guardarDatosGenerales();
    printf("Datos generales actualizados.\n");
}

//Calculos del viaje
void calcularCostoViaje() {
    if (totalVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    listarVehiculos();
    printf("Seleccione un vehiculo: ");
    int opcion; scanf("%d", &opcion);
    if (opcion < 1 || opcion > totalVehiculos) {
        printf("Seleccion invalida.\n");
         return;
    }
    Vehiculo v = vehiculos[opcion-1];

    float km_totales, porcentaje_ciudad;
    printf("Km totales del viaje: "); scanf("%f", &km_totales);
    if (km_totales <= 0) { printf("Los km deben ser mayores a 0.\n"); return; }
    printf("Porcentaje en ciudad (0-100): "); scanf("%f", &porcentaje_ciudad);
    if (porcentaje_ciudad < 0 || porcentaje_ciudad > 100) {
        printf("Porcentaje invalido.\n"); return;
    }
    //Conversion y calculo del porcentaje de kilometros en ciudad o carretera
    float km_ciudad = (porcentaje_ciudad / 100.0f) * km_totales;
    float km_carretera = km_totales - km_ciudad;
    //calculos de combustibles
    float costo_combustible_tipo = (strcmp(v.tipo_combustible, "gasolina") == 0) ? datosGenerales.costo_gasolina : datosGenerales.costo_gasoil;
    float costo_combustible = (km_ciudad / v.km_por_galon_ciudad) * costo_combustible_tipo + (km_carretera / v.km_por_galon_carretera) * costo_combustible_tipo;
    //calculos de gomas, seguro y mantenimiento en el viaje
    float costo_gomas_viaje = (v.costo_gomas / v.km_vida_gomas) * km_totales;
    float costo_seguro_viaje = (v.costo_seguro_anual / v.km_promedio_anual) * km_totales;
    float costo_mantenimiento_viaje = (v.costo_mantenimiento / v.km_mantenimiento) * km_totales;
    // Cálculo de depreciación sin valor de reventa
    float km_vida_util = v.km_promedio_anual * v.vida_util_anios;
    float depreciacion_km = v.costo_vehiculo / km_vida_util;
    float costo_depreciacion_viaje = depreciacion_km * km_totales;

    float costo_total = costo_combustible + costo_gomas_viaje + costo_seguro_viaje + costo_mantenimiento_viaje + costo_depreciacion_viaje;
    float costo_por_km = costo_total / km_totales;

    printf("\n---- DESGLOSE DE COSTOS ----\n");
    printf("Combustible:    %.2f\n", costo_combustible);
    printf("Gomas:          %.2f\n", costo_gomas_viaje);
    printf("Seguro:         %.2f\n", costo_seguro_viaje);
    printf("Mantenimiento:  %.2f\n", costo_mantenimiento_viaje);
    printf("Depreciacion:  %.2f\n", costo_depreciacion_viaje);
    printf("----------------------------\n");
    printf("TOTAL:          %.2f\n", costo_total);
    printf("Costo por km:   %.2f\n", costo_por_km);
}

//Menu
int main() {
    cargarVehiculos();
    cargarDatosGenerales();

    int opcion;
    do {
        printf("\n--- GESTION DE COSTO POR KILOMETRO ---\n");
        printf("1. Gestion de vehiculos (Crear/Listar/Borrar)\n");
        printf("2. Gestion de datos generales (Precio de Combustibles)\n");
        printf("3. Calcular costo de viaje\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) { return 0; }

        switch(opcion) {
            case 1: {
                int subop;
                printf("\n1. Crear vehiculo\n2. Listar vehiculos\n3. Borrar vehiculo\nOpcion: ");
                scanf("%d", &subop);
                if (subop == 1) crearVehiculo();
                else if (subop == 2) listarVehiculos();
                else if (subop == 3) borrarVehiculo();
                else printf("Opcion invalida.\n");
                break;
            }
            case 2:
                modificarDatosGenerales();
                break;
            case 3:
                calcularCostoViaje();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}