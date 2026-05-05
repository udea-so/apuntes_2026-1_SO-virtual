#include <stdio.h>
#include <stdlib.h> // Necesaria para malloc y free
#include "common.h" // Para GetTime()

int main() {
    const int TAMANO = 1000000000;
    int* v1 = (int*)malloc(TAMANO * sizeof(int));
    int* v2 = (int*)malloc(TAMANO * sizeof(int));
    int* resultado = (int*)malloc(TAMANO * sizeof(int));

    if (!v1 || !v2 || !resultado) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Inicializar vectores (igual que antes)
    for (int i = 0; i < TAMANO; i++) {
        v1[i] = i;
        v2[i] = i * 2;
    }

    // ======================================================
    // Medición de la versión serial
    // ======================================================

    printf("Ejecutando la suma en modo serial...\n");
    
    // INICIA LA MEDICIÓN
    double t_inicio_serial = GetTime();

    // Un único bucle que hace todo el trabajo
    for (int i = 0; i < TAMANO; i++) {
        resultado[i] = v1[i] + v2[i];
    }
    
    // FINALIZA LA MEDICIÓN
    double t_fin_serial = GetTime();
    double tiempo_serial = t_fin_serial - t_inicio_serial;

    printf("Tiempo de ejecución serial (Ts): %f segundos.\n", tiempo_serial);

    // Liberar memoria
    free(v1);
    free(v2);
    free(resultado);

    return 0;
}