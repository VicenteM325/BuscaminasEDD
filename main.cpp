#include <cstdio>
#include <cstdlib>
#include <ctime>

#define FILAS 6
#define COLUMNAS 6
#define MINAS 8

int tablero[FILAS][COLUMNAS];
int tableroVisible[FILAS][COLUMNAS];

void inicializarTablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = 0;
            tableroVisible[i][j] = 0;
        }
    }
}

void colocarMinas() {
    srand(time(NULL));

    for (int i = 0; i < MINAS; i++) {
        int fila, columna;
        do {
            fila = rand() % FILAS;
            columna = rand() % COLUMNAS;
        } while (tablero[fila][columna] == -1);

        tablero[fila][columna] = -1;
    }
}

void mostrarTablero() {
    printf("   ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("%d  ", j);
    }
    printf("\n");

    printf("   ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%d |", i);
        for (int j = 0; j < COLUMNAS; j++) {
            if (tableroVisible[i][j] == 0) {
                printf(".  ");
            } else if (tablero[i][j] == -1) {
                printf("*  ");
            } else {
                printf("%d  ", tablero[i][j]);
            }
        }
        printf("\n");
    }
}

int contarMinasAlrededor(int fila, int columna) {
    int contador = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nuevaFila = fila + i;
            int nuevaColumna = columna + j;

            if (nuevaFila >= 0 && nuevaFila < FILAS && nuevaColumna >= 0 && nuevaColumna < COLUMNAS) {
                if (tablero[nuevaFila][nuevaColumna] == -1) {
                    contador++;
                }
            }
        }
    }

    return contador;
}

void destaparCasilla(int fila, int columna) {
    if (tablero[fila][columna] == -1) {
        printf("¡Boom!.\n");
        printf("Las minas estaban en las siguientes ubicaciones:\n");
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (tablero[i][j] == -1) {
                    printf("*  ");
                } else {
                    printf("%d  ", contarMinasAlrededor(i, j));
                }
            }
            printf("\n");
        }
        exit(0);
    } else {
        int minasAlrededor = contarMinasAlrededor(fila, columna);
        tableroVisible[fila][columna] = 1;

        if (minasAlrededor == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int nuevaFila = fila + i;
                    int nuevaColumna = columna + j;

                    if (nuevaFila >= 0 && nuevaFila < FILAS && nuevaColumna >= 0 && nuevaColumna < COLUMNAS) {
                        if (tableroVisible[nuevaFila][nuevaColumna] == 0) {
                            destaparCasilla(nuevaFila, nuevaColumna);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    inicializarTablero();
    colocarMinas();

    while (1) {
        mostrarTablero();

        int fila, columna;
        printf("\nIngrese fila y columna: ");
        scanf("%d %d", &fila, &columna);

        if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
            if (tableroVisible[fila][columna] == 0) {
                destaparCasilla(fila, columna);
            } else {
                printf("Casilla ya destapada. Ingrese otra.\n");
            }
        } else {
            printf("Coordenadas fuera del rango. Ingrese nuevamente.\n");
        }
    }

}