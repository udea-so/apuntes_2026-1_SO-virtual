# Experimento: Contador Aproximado (Sloppy Counter)

## 1. Descripción general

El presente experimento tiene como propósito analizar el comportamiento de un **contador compartido concurrente** bajo diferentes estrategias de sincronización. En particular, se estudia una implementación denominada **contador aproximado (sloppy counter)**, la cual busca reducir la contención de bloqueos mediante el uso de contadores **locales por CPU** y actualizaciones periódicas del valor global.

Este ejercicio hace parte del módulo de **concurrencia y sincronización** del curso de *Sistemas Operativos* y permite contrastar la eficiencia y precisión entre diferentes mecanismos de acceso a recursos compartidos.

---

## 2. Archivos proporcionados

| Archivo | Descripción |
|----------|-------------|
| `sloppy_counter.h` | Define la estructura del contador, las variables globales, los locks y los prototipos de las funciones `init`, `update` y `get`. |
| `sloppy_counter.c` | Implementa la lógica del contador aproximado, incluyendo la inicialización, la actualización concurrente y la obtención del valor global. |
| `main_sloppy_counter.c` | Ejemplo base de uso del contador con un número fijo de hilos. |
| `benchmark_sloppy_counter.c` | Programa principal para medir el desempeño y la precisión del contador al variar el número de hilos. |
| `benchmark_thresh_amt1.c` | Programa adicional para analizar el efecto del parámetro `threshold` (umbral de actualización global) sobre el tiempo de ejecución. |
| `results_sloppy.csv` y `results_thresh_amt1.csv` | Archivos de salida generados por los benchmarks con los resultados experimentales. |

---

## 3. Compilación de los programas

Desde la terminal, ubíquese en el directorio donde se encuentran los archivos y ejecute los siguientes comandos según el programa que desee compilar.

### a. Ejemplo básico de ejecución

```bash
gcc -Wall sloppy_counter.c main_sloppy_counter.c -lpthread -o sloppy_example
```

### b. Benchmark de desempeño (variando número de hilos)

```bash
gcc -Wall sloppy_counter.c benchmark_sloppy_counter.c -lpthread -o benchmark_sloppy
```

### c. Benchmark de umbral (`threshold`)

```bash
gcc -Wall sloppy_counter.c benchmark_thresh_amt1.c -lpthread -o benchmark_thresh
```

Cada uno de estos comandos generará un archivo ejecutable (`.out` u otro nombre definido en `-o`).

---

## 4. Ejecución de los experimentos

### a. Prueba simple

Ejecute el programa base con:

```bash
./sloppy_example
```

El programa mostrará el número de hilos, el tiempo total de ejecución y el valor aproximado del contador.

### b. Benchmark del contador

Ejecute el benchmark principal para observar el desempeño con diferentes números de hilos:

```bash
./benchmark_sloppy
```

Este programa generará un archivo `results_sloppy.csv` con el siguiente formato:

```
Threads,Time(s),Expected,Actual
1,0.0042,1000000,1000000
2,0.0105,2000000,1999920
...
```

### c. Benchmark de variación del umbral (`threshold`)

Para analizar el impacto del parámetro `threshold`, ejecute:

```bash
./benchmark_thresh
```

Este generará el archivo `results_thresh_amt1.csv`, que contiene los resultados de tiempo de ejecución para distintos valores de umbral.



## 5. Interpretación general

- El **contador aproximado** busca disminuir la contención sobre el bloqueo global (`glock`) distribuyendo el conteo entre estructuras locales por CPU.  
- Cada hilo actualiza su contador local y solo transfiere su valor al global cuando este supera un **umbral (`threshold`)** predefinido.  
- El valor final reportado puede no ser exacto, pero el tiempo de ejecución se reduce significativamente frente al uso de un solo bloqueo global.

---

## 6. Análisis de resultados

Se recomienda analizar los archivos `.csv` obtenidos mediante herramientas como **Python (pandas + matplotlib)**, **Excel** o **Jupyter Notebook**, generando gráficas que relacionen:

1. Tiempo de ejecución vs. número de hilos.  
2. Valor esperado vs. valor obtenido.  
3. Tiempo de ejecución vs. umbral (`threshold`).

Estos resultados permiten discutir el equilibrio entre **rendimiento y precisión** en los sistemas concurrentes.

## 7. Conclusión

Este experimento proporciona una base práctica para comprender cómo la **sincronización fina (fine-grained locking)** y la **relajación del control global** pueden mejorar el rendimiento en entornos concurrentes. Sin embargo, también pone de manifiesto la pérdida de exactitud y la necesidad de elegir cuidadosamente los parámetros de actualización según el contexto de aplicación.

> [!note]
> **Nota sobre IA**: Este contenido fue elaborado y estructurado con la asistencia de un modelo de inteligencia artificial. Tenga en cuenta que puede contener errores.

> [!warning]
> **Aclaración**: Como todo código (especialmente los ejemplos didácticos diseñados pueden fallar (o de hecho fallan)), el contenido debe ser revisado críticamente y puede contener errores.