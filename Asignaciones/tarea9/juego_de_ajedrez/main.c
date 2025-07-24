#include <stdio.h>

char tablero[8][8] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'},
    {'R','N','B','Q','K','B','N','R'}
};
// Esta funcion imprime el tablero, iniciando por el encabezado y siguiendo con un bucle que imprime el numero de fila del 8 al 1, luego un bucle interno que imprime los espacios y piezas del tablero.
void mostrar_tablero(){
    printf("\n\t  a b c d e f g h\n");  // encabezado
    for (int fila = 0; fila < 8; fila++) {
        printf("\t");
        printf("%d ", 8 - fila);  // imprime nmero de fila
        for (int columna = 0; columna < 8; columna++) {
           printf("%c ", tablero[fila][columna]);  // muestra pieza o espacio
        }

        printf("%d\n", 8 - fila);  // numero de fila al final
    }
    printf("\t  a b c d e f g h\n");  // pie
}
// Esta funcion usa el valor interno de a(97) para convertir cualquier letra del tablero a su representacion numerica. 
// Los valores de cada letra son: a=97, b=98, c=99, d=100, e=101, f=102, g=103, h=104.
int letra_a_columna(char letra){
    return letra - 'a';  // por ejemplo, 'a'  0, 'b'  1, ..., 'h'  7
}
// Esta funcion convierte el caracter numerico que escribe el usuario al indice que necesita la matriz.
// El caractet '0' vale 48 en ASCII, '1'= 49, '2'= 50, ..., '8'=56. 
int numero_a_fila(char numero){
     return 8 - (numero - '0');  // por ejemplo, '2'  fila 6
}

// Esta funcion es la regla para determinar si el movimiento que quiere hacer el jugador es valido, comparando la posicion de la pieza con respecto al tablero.
int dentro_del_tablero(int fila, int columna){
    return fila >= 0 && fila < 8 && columna >= 0 && columna < 8;
}

int identificar_color_pieza(char pieza){
    if(pieza >= 'A' && pieza <= 'Z' ){
        return 0; // Blanco
    }else if(pieza >= 'a' && pieza <= 'z'){
        return 1; // Negra
    }else 
        return 2; // Casilla vacia
}


int mover_pieza(char origen_col, char origen_fila_char, char destino_col, char destino_fila_char){
    int fila_origen = numero_a_fila(origen_fila_char);          //Esta seccion convierte todos los valores en string, dados por el usuario
    int col_origen = letra_a_columna(origen_col);               // a valores numericos enteros.
    int fila_destino = numero_a_fila(destino_fila_char);
    int col_destino = letra_a_columna(destino_col); 

    // Por medio del operador NOT y la funcion dentro_del_tablero, se verifica que las coordenadas dadas sean validas.
    if (!dentro_del_tablero(fila_origen, col_origen) || !dentro_del_tablero(fila_destino, col_destino)){
        printf("Coordenadas fuera del tablero!\n");
        return 0;
    }

    // Verifica si hay una pieza en la casilla de origen
    char pieza = tablero[fila_origen][col_origen];
    if (pieza == ' '){
        printf("No hay pieza en la casilla de origen!\n");
        return 0;
    }
    // Verifica si el destino tiene una pieza del mismo color
    char origen_pieza = tablero[fila_origen][col_origen];
    char destino_pieza = tablero[fila_destino][col_destino];

    if(identificar_color_pieza(origen_pieza) == identificar_color_pieza(destino_pieza)){
        printf("No puedes mover sobre una pieza de tu mismo color!!\n");
        return 0;
    }

    // Mover la pieza
    tablero[fila_destino][col_destino] = pieza;
    tablero[fila_origen][col_origen] = ' ';
    return 1;
}

int main(){
    char origen[3], destino[3];  // ejemplo: origen = "e2", destino = "e4"
    int turno_blancas = 1;

    printf("\n\t   Ajedrez en C!!\n");

    while (1) {
        mostrar_tablero();

        if (turno_blancas) {
            printf("\n--------------------------------------");
            printf("\n\nTurno de Blancas (ej. e2 e4): ");
        } else {
            printf("\n--------------------------------------");
            printf("\n\nTurno de Negras (ej. e7 e5): ");
        }

        scanf("%2s %2s", origen, destino);  // leer entrada del usuario

        // Llamar a la funcin de mover
        int exito = mover_pieza(origen[0], origen[1], destino[0], destino[1]);

        if (exito) {
            turno_blancas = !turno_blancas;  // cambiar turno
        }
    }

    return 0;
}
