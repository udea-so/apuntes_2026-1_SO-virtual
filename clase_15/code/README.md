# Lock examples - Resumen y guía rápida

## Codigos

- [**`compare-and-swap.c`**](compare-and-swap.c): Demostración de CAS (instrucción atómica `cmpxchg`) en ensamblador inline.
- [**`t1_lock.c`**](t1_lock.c): Ejemplo en C con `pthreads` y `pthread_mutex_t` (protege un contador compartido).
- [**`t1_lock.py`**](t1_lock.py): Ejemplo equivalente en Python usando `threading.Lock`.

## Sobre los codigos

### 1. `compare-and-swap.c`

Uso de compare-and-swap (`cmpxchg`) para actualizar una variable de forma atómica; el programa imprime resultado de una CAS exitosa y otra fallida.

#### Compilación

```
gcc -o compare-and-swap compare-and-swap.c -Wall
```
#### Ejecución

```
./compare-and-swap
```

#### Salida esperada (ejemplo):

```
before successful cas: 0
after successful cas: 100 (success: 1)
before failing cas: 100
after failing cas: 100 (old: 0)
```

### 2. `t1_lock.c` 

Dos hilos incrementan un contador compartido; se usa `pthread_mutex_t` para evitar condiciones de carrera. Comprueba que el resultado final coincide con el esperado (max * 2).

#### Compilación

```
gcc -o t1_lock t1_lock.c -lpthread -Wall
```
#### Ejecutación

Ejemplo con 1000000 iteraciones por hilo:

```
./t1_lock 1000000
```

#### Salida esperada

```
main: begin [counter = 0]
A: done
B: done
main: done
[counter: 2000000]
[should: 2000000]
```

### 3. `t1_lock.py` (Python)

Versión en Python que usa `threading.Lock` para sincronizar incrementos. Útil para comparar legibilidad y comportamiento alto nivel.

#### Ejecución

```
python3 t1_lock.py 1000000
```

La salida esperada similar a la del ejemplo en C: el contador final debe ser `max * 2`.

### Consejos de uso y pruebas
- Variar el parámetro de iteraciones para ver escalado/tiempos:
  - pequeño: 1000
  - medio: 100000
  - grande: 1000000
- Repetir varias ejecuciones para observar estabilidad.
- Para experimentar condiciones de carrera, eliminar/comentar las adquisiciones del lock en los ejemplos (solo con fines didácticos).

### Limpieza

```
rm -f compare-and-swap t1_lock
```

> [!important]
> - `compare-and-swap.c` demuestra primitiva atómica de bajo nivel (útil para construir locks sin bloqueo).
> - `t1_lock.c` y `t1_lock.py` muestran el uso práctico de locks para proteger una sección crítica.

> [!note]
> **Nota sobre IA**: Este contenido fue elaborado y estructurado con la asistencia de un modelo de inteligencia artificial. 

> [!warning]
> **Aclaración**: Como todo código (especialmente los ejemplos didácticos diseñados pueden fallar (o de hecho fallan)), el contenido debe ser revisado críticamente y puede contener errores.
