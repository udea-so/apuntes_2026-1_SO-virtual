# Contador Preciso con Mutex 

## Estructura de archivos

```
precise_counter/
├── benchmark_precise_counter.c  # Programa de benchmarking
├── counter_lock.c              # Implementación del contador con mutex
├── counter_lock.h              # Definiciones y estructuras
└── main_precise_counter.c      # Programa de prueba simple
```

## Compilacion

1. **Programa de prueba simple**
   
   ```
   gcc -Wall -I./include counter_lock.c main_precise_counter.c -lpthread -o precise_counter
   ```

2. **Programa de benchmark**
   
   ```
   gcc -Wall -I./include counter_lock.c benchmark_precise_counter.c -lpthread -o benchmark_precise_counter
   ```
   
## Ejecución de experimentos

1. **Prueba simple (16 threads)**
   
   ```
   ./precise_counter
   ```

   Este comando ejecutará una prueba con 16 threads, cada uno incrementando el contador 1000000 de veces.


2. **Benchmark completo**
   
   ```
   ./benchmark_precise_counter
   ```

   Este comando:
   - Ejecuta pruebas con 1, 2, 4, 8 y 16 threads
   - Genera archivo `results_lock.csv` con los resultados
   - Muestra progreso en consola

3. **Verificación de resultados**

   - Comparar "Valor esperado" vs "Valor real" en la salida
   - Con mutex, deberían ser siempre igual

## Notas importantes

- Este contador usa mutex para sincronización
- Garantiza corrección pero puede ser más lento
- El archivo CSV generado puede usarse para comparar con otras implementaciones
- Los resultados pueden variar según el hardware

## Limpieza

Use el siguiente comando para eliminar los ejecutables generados al compilar: 

```
rm -f precise_counter benchmark_precise_counter results_lock.csv
```

## Notas importantes

Para reproducir completamente el experimento, ejecutar en orden los pasos descritos en la sección de ejecución de experimentos:
1. Compilar programas
2. Ejecutar benchmark
3. Visualizar resultados con el notebook

> [!note]
> **Nota sobre IA**: Este contenido fue elaborado y estructurado con la asistencia de un modelo de inteligencia artificial. Tenga en cuenta que puede contener errores.

> [!warning]
> **Aclaración**: Como todo código (especialmente los ejemplos didácticos diseñados pueden fallar (o de hecho fallan)), el contenido debe ser revisado críticamente y puede contener errores.