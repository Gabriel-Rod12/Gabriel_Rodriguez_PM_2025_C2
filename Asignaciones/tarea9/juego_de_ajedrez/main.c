#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char tablero[8][8] = {
    {'t','c','a','d','r','a','c','t'},
    {'p','p','p','p','p','p','p','p'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'},
    {'T','C','A','D','R','A','C','T'}
};
int turno_blancas = 1;
// Esta funcion imprime el tablero, iniciando por el encabezado y siguiendo con un bucle que imprime el numero de fila del 8 al 1, luego un bucle interno que imprime los espacios y piezas del tablero.
void mostrar_tablero(){
    printf("\n\t    a b c d e f g h\n");  // encabezado
    printf("\t   -----------------\n");
    for (int fila = 0; fila < 8; fila++) {
        printf("\t");
        printf("%d | ", 8 - fila);  // imprime nmero de fila
        for (int columna = 0; columna < 8; columna++) {
           printf("%c ", tablero[fila][columna]);  // muestra pieza o espacio
        }

        printf("| %d\n", 8 - fila);  // numero de fila al final
    }
    printf("\t   -----------------\n");
    printf("\t    a b c d e f g h\n");  // pie
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
    }else {
        return 2; // casilla vacia 
    }
}
// por medio de la funcion toupper se puede cambiar un caracter en minuscula a uno en mayuscula, asi si llega una pieza 'p' se convierte en 'P' y no es necesario validar ambas. 
int identificar_pieza(char tipo_pieza){
    switch (toupper(tipo_pieza)) {
        case 'P': return 1; // Peon
        case 'T': return 2; // Torre
        case 'C': return 3; // Caballo
        case 'A': return 4; // Alfil
        case 'D': return 5; // Reina
        case 'R': return 6; // Rey
        default: return 0; // No es una pieza valida
    }

}

int movimiento_peon(int fila_origen, int col_origen, int fila_destino, int col_destino, char pieza){
    int direccion = (pieza == 'P') ? -1 : 1; //Blancas suben, Negras bajan
    int fila_inicial = (pieza == 'P') ? 6 : 1; // Identificador para fila inicial del peon
    int es_blanco = (pieza == 'P'); // Identificador para saber si el peon es blanco
    char destino = tablero[fila_destino][col_destino]; // Destino del movimiento de la pieza
    int delta_fila = fila_destino - fila_origen; // movimiento de la pieza en filas
    int delta_col = col_destino - col_origen; // movimiento de la pieza en columnas

    if(delta_col == 0 && delta_fila == direccion && destino == ' '){
        if ((es_blanco && fila_destino == 0) || (!es_blanco && fila_destino == 7)){
            return 2;
        } 
        return 1;
    } else if(delta_col == 0 && delta_fila == 2 * direccion && fila_origen == fila_inicial && tablero[fila_origen + direccion][col_origen] == ' ' && destino == ' '){
        return 1;
    } else if(abs(delta_col) == 1 && delta_fila == direccion && destino != ' ' && identificar_color_pieza(destino) != identificar_color_pieza(pieza)){
        if ((es_blanco && fila_destino == 0) || (!es_blanco && fila_destino == 7)){
            return 2;
        } 
        return 1;
    }

 
    return 0;
}

int movimiento_torre(int fila_origen, int col_origen, int fila_destino, int col_destino){
    //Verifica que el movimiento sea en linea recta
    if(fila_origen != fila_destino && col_origen != col_destino){
        return 0;
    }

    if(col_origen == col_destino){
        int paso = (fila_destino > fila_origen) ? 1 : -1;
        for (int f = fila_origen + paso; f != fila_destino; f+= paso){
            if(tablero[f][col_origen] != ' '){
                return 0;
            }
        }
        
    }

    if(fila_origen == fila_destino){
        int paso = (col_destino > col_origen) ? 1 : -1;
        for(int c = col_origen + paso; c != col_destino; c += paso){
            if (tablero[fila_origen][c] != ' '){
                return 0;
            }
            
        }
    }
    return 1;
}

int movimiento_caballo(int fila_origen, int col_origen, int fila_destino, int col_destino){
    int delta_fila = abs(fila_destino - fila_origen);
    int delta_col = abs(col_destino - col_origen);

    //Validacion del movimiento en L
    if(!((delta_fila == 2 && delta_col == 1) || (delta_fila == 1 && delta_col == 2))){
        return 0;
    }
    return 1;
}

int movimiento_alfil(int fila_origen, int col_origen, int fila_destino, int col_destino){
    int delta_fila = fila_destino - fila_origen;
    int delta_col = col_destino - col_origen;

    // El alfil solo se puede mover en diagonales: |Δfila| == |Δcolumna|
    if (abs(delta_fila) != abs(delta_col)) {
        return 0;
    }
    // Determinar dirección de movimiento
    int paso_fila = (delta_fila > 0) ? 1 : -1;
    int paso_col = (delta_col > 0) ? 1 : -1;
    // Verificar que todas las casillas entre origen y destino estén vacías
    int f = fila_origen + paso_fila;
    int c = col_origen + paso_col;
    while (f != fila_destino && c != col_destino) {
        if (tablero[f][c] != ' ') {
            return 0;  // Hay una pieza en el camino
        }
        f += paso_fila;
        c += paso_col;
    }
    return 1;
}

int movimiento_reina(int fila_origen, int col_origen, int fila_destino, int col_destino){
    int delta_fila = fila_destino - fila_origen;
    int delta_col = col_destino - col_origen;

    // Verificar si el movimiento es en línea recta (torre) o en diagonal (alfil)
    if (delta_fila == 0 || delta_col == 0 || abs(delta_fila) == abs(delta_col)) {
        int paso_fila = (delta_fila == 0) ? 0 : (delta_fila > 0 ? 1 : -1);
        int paso_col = (delta_col == 0) ? 0 : (delta_col > 0 ? 1 : -1);

        int fila_actual = fila_origen + paso_fila;
        int col_actual = col_origen + paso_col;

        // Verificar que el camino esté libre
        while(fila_actual != fila_destino || col_actual != col_destino){
            if(tablero[fila_actual][col_actual] != ' '){
                return 0; // Hay una pieza en el camino
            }
            fila_actual += paso_fila;
            col_actual += paso_col;
        }

        // El movimiento es válido
        return 1;
    }

    return 0; // Movimiento inválido
}

int movimiento_rey(int fila_origen, int col_origen, int fila_destino, int col_destino){
    int delta_fila = abs(fila_destino - fila_origen);
    int delta_col = abs(col_destino - col_origen);
    // Verifica que el movimiento sea de una sola casilla en cualquier dirección
    if (delta_fila <= 1 && delta_col <= 1){
        return 1;
    }

    return 0; // Movimiento inválido
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

     // Verifica si el jugador intenta mover una pieza de su color
    int es_blanca = (pieza >= 'A' && pieza <= 'Z');
    if ((turno_blancas && !es_blanca) || (!turno_blancas && es_blanca)) {
        printf("No puedes mover piezas del oponente.\n");
        return 0;
    }

    // Verifica si el destino tiene una pieza del mismo color
    char origen_pieza = tablero[fila_origen][col_origen];
    char destino_pieza = tablero[fila_destino][col_destino];

    if(identificar_color_pieza(origen_pieza) == identificar_color_pieza(destino_pieza)){
        printf("No puedes moverte sobre una pieza de tu mismo color!!\n");
        return 0;
    }

    int tipo = identificar_pieza(pieza);
    int movimiento_valido = 0;

    switch(tipo){
        case 1: {
            int res = movimiento_peon(fila_origen, col_origen, fila_destino, col_destino, pieza);     
            if(res == 0){
                printf("Movimiento invalido para el peon.\n");
                return 0;
            }else if(res == 2){
                // Promoción
                char nueva_pieza;
                int es_blanco = (pieza == 'P');
                printf("Peon llega al final! Elige una promoción (D = Reina  T = Torre  A = Alfil  C = Caballo): ");
                scanf(" %c", &nueva_pieza);
                nueva_pieza = toupper(nueva_pieza);
                switch(nueva_pieza){
                    case 'D': pieza = es_blanco ? 'D' : 'd'; break;
                    case 'T': pieza = es_blanco ? 'T' : 't'; break;
                    case 'A': pieza = es_blanco ? 'A' : 'a'; break;
                    case 'C': pieza = es_blanco ? 'C' : 'c'; break;
                    default:
                        printf("Promocion invalida, se asigna Reina por defecto.\n");
                        pieza = es_blanco ? 'D' : 'd';
                }
            }
            movimiento_valido = 1;
            break;
        }    
        case 2: movimiento_valido =  movimiento_torre(fila_origen, col_origen, fila_destino, col_destino);     
            break;
        case 3: movimiento_valido =  movimiento_caballo(fila_origen, col_origen, fila_destino, col_destino);     
            break;
        case 4: movimiento_valido = movimiento_alfil(fila_origen, col_origen, fila_destino, col_destino);
            break;
        case 5: movimiento_valido = movimiento_reina(fila_origen, col_origen, fila_destino, col_destino);
            break;
        case 6: movimiento_valido = movimiento_rey(fila_origen, col_origen, fila_destino, col_destino);
            break;
        default:
            movimiento_valido = 1;
            break;
    }
    
    if(movimiento_valido){
        tablero[fila_destino][col_destino] = pieza;
        tablero[fila_origen][col_origen] = ' ';
        return 1;
    }else{
        printf("Movimiento invalido para esa pieza.\n");
        return 0;
    }
    return 1;
}

int main(){
    char origen[3], destino[3];  // ejemplo: origen = "e2", destino = "e4"

    printf("\n\t   Ajedrez en C!!\n");

    while(1){
        mostrar_tablero();

        if (turno_blancas){
            printf("\n--------------------------------------");
            printf("\n\nTurno de Blancas (ej. e2 e4): ");
        }else{
            printf("\n--------------------------------------");
            printf("\n\nTurno de Negras (ej. e7 e5): ");
        }

        scanf("%2s %2s", origen, destino);  // leer entrada del usuario

        // Llamar a la funcin de mover
        int exito = mover_pieza(origen[0], origen[1], destino[0], destino[1]);

        if (exito){ 
            turno_blancas = !turno_blancas;  // cambiar turno
        }
    }
    return 0;
}
