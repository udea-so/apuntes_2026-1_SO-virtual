# Contador sin locks - Resumen y pruebas

## Resumen de los archivos

- [counter_without_locks.c](counter_without_locks.c)
  - Programa principal que crea NUM_THREADS (8) hilos y cada hilo incrementa el contador CNT_END (1_000_000).
  - Mide tiempo total y muestra el valor esperado vs el valor real.
  - Usa la implementación en [counter.c](counter.c) (sin sincronización).

- [counter.c](counter.c)
  - Implementación simple del contador:
    - **init**: pone `value = 0`
    - **increment**: `value++`
    - **decrement**: `value--`
    - **get**: devuelve `value`

- [counter.h](counter.h)
  - Definición del tipo `counter_t` y prototipos de funciones.

- [test_counter_cli.c](test_counter_cli.c) (en el mismo directorio)
  - Versión que acepta argumentos CLI: `./counter_test <num_threads> <count_per_thread>`
  - Útil para probar diferentes configuraciones sin recompilar.

## Compilación y enlazado

Ubicado en el directorio `counter_without_locks`. Ejecute los siguientes comandos de compilación y enlazado:
- Ejecutable con parámetros fijos (bad_counter):
    
  ```
  gcc -Wall -I./include counter.c counter_without_locks.c -lpthread -o bad_counter
  ```
- Ejecutable CLI (counter_test):
    
  ```
  gcc -Wall -I./include test_counter_cli.c counter.c -lpthread -o counter_test
  ```

## Ejecución y pruebas recomendadas

1. Prueba básica (valores fijos):
  ```
  ./bad_counter
  ```

2. Prueba configurable (ejemplos):
  
  ```
  ./counter_test 1 1000000
  ./counter_test 2 500000
  ./counter_test 4 100000
  ./counter_test 8 1000000
  ```

## Experimentos útiles:

1. Escalabilidad (mismo work, distintos hilos):
    
   ```
   for t in 1 2 4 8 16; do ./counter_test $t 100000; done
   ```

2. Carga (mismo hilos, distinto work):
   
   ```
   for n in 1000 10000 100000 1000000; do ./counter_test 4 $n; done
   ```

3. Repetir ejecución para observar variabilidad por condiciones de carrera:
   
   ```
   for i in {1..5}; do ./counter_test 8 1000000; done
   ```

## Observaciones

- Dado que `increment` no está sincronizado, se producirán condiciones de carrera.
- El valor real del contador probablemente será menor que el valor esperado.
- Los tiempos mostrados sirven para comparar rendimiento, pero la corrección del resultado no está garantizada.

## Comparación con versión sincronizada (opcional)
- Para comparar, puede implementar una versión con mutex en `counter.c`/`counter.h` (añadir pthread_mutex_t en `counter_t` y proteger `increment`/`decrement` con lock/unlock). Esto mostrará tiempos mayores pero resultados correctos.

> [!Note]
> Esto se realizara en el proximos ejemplo

## Cleanup

Para eliminar los archivos binarios, ejecute el siguiente comando:

```
rm -f bad_counter counter_test
```

> [!note]
> **Nota sobre IA**: Este contenido fue elaborado y estructurado con la asistencia de un modelo de inteligencia artificial. Tenga en cuenta que puede contener errores.

> [!warning]
> **Aclaración**: Como todo código (especialmente los ejemplos didácticos diseñados pueden fallar (o de hecho fallan)), el contenido debe ser revisado críticamente y puede contener errores.