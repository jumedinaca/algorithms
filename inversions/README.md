
# Taller: Contar inversiones — fuerza bruta vs. dividir y conquistar

## 1. Descripción

Dos personas ordenaron las mismas `n` películas. Los gustos de la primera definen el orden de referencia `1, 2, ..., n`, y la segunda entrega su ranking como una lista `a₁, ..., aₙ`.

Una **inversión** es un par de posiciones `i < j` tales que `aᵢ > aⱼ` (estricto).

- `0` inversiones significa que ambos rankings coinciden.
- `n(n−1)/2` inversiones significa que los rankings son exactamente opuestos.

En este taller se implementan dos algoritmos para contar inversiones:

- **Fuerza bruta:** revisa todos los pares `(i, j)` con `i < j`.
- **Dividir y conquistar:** una variante de Merge Sort que cuenta las inversiones mientras mezcla.

### Pregunta central

¿Cuántas comparaciones ahorra el algoritmo de dividir y conquistar? ¿Siempre hace menos comparaciones que la fuerza bruta? ¿Cómo cambia el número de comparaciones según el tipo de arreglo?

Para cada arreglo de entrada, el programa debe ejecutar ambos algoritmos y reportar el número de inversiones y cuántas comparaciones de elementos realizó cada uno.

## 2. Fuerza bruta

**Idea:** para cada par de posiciones `i < j`, comparar `A[i]` con `A[j]` y contar si `A[i] > A[j]`.

### Pseudocódigo

```text
BRUTE-FORCE-INVERSIONS(A)

    count = 0

    for i = 1 to A.length - 1
        for j = i + 1 to A.length
            if A[i] > A[j]        // 1 comparación
                count = count + 1

    return count
```

### Conteo de comparaciones

Cada evaluación de `A[i] > A[j]` cuenta como una comparación, sea verdadera o falsa.

Este algoritmo siempre realiza exactamente la misma cantidad de comparaciones para un tamaño `n` dado:

`n(n−1)/2`

## 3. Dividir y conquistar

**Idea:** las inversiones de `A[p..r]` son de tres clases:

1. Inversiones con ambas posiciones en la mitad izquierda.
2. Inversiones con ambas posiciones en la mitad derecha.
3. Inversiones cruzadas, con un elemento en cada mitad.

Las dos primeras se cuentan recursivamente. Las inversiones cruzadas se cuentan durante `MERGE-COUNT`.

Cuando se toma un elemento de la mitad derecha antes de que se hayan tomado todos los elementos restantes de la izquierda, ese elemento es menor que todos los que quedan en la izquierda. Por tanto, cada uno de esos elementos forma una inversión con él.

### Pseudocódigo

```text
COUNT-INVERSIONS(A, p, r)

    if p >= r
        return 0

    q = floor((p + r) / 2)

    left  = COUNT-INVERSIONS(A, p, q)
    right = COUNT-INVERSIONS(A, q + 1, r)
    cross = MERGE-COUNT(A, p, q, r)

    return left + right + cross
```

### MERGE-COUNT

```text
MERGE-COUNT(A, p, q, r)

    n1 = q - p + 1
    n2 = r - q

    L = A[p..q]
    R = A[q+1..r]

    i = 1
    j = 1
    k = p
    cross = 0

    while i <= n1 and j <= n2
        if L[i] <= R[j]       // 1 comparación
            A[k] = L[i]
            i = i + 1
        else
            A[k] = R[j]
            j = j + 1
            cross = cross + (n1 - i + 1)

        k = k + 1

    copiar a A los elementos restantes de L, si quedan
    copiar a A los elementos restantes de R, si quedan

    return cross
```

### Conteo de comparaciones

Cada evaluación de `L[i] <= R[j]` dentro del `while` cuenta como una comparación.

La copia de los elementos restantes no cuenta como comparación.

Es importante respetar el siguiente esquema:

- División en `q = floor((p+r)/2)`.
- Tomar el elemento de `L` cuando existe igualdad.
- Usar `<=` en lugar de `<`, para evitar contar elementos repetidos como inversiones.

El número de inversiones debe ser idéntico en ambos algoritmos.

### Complejidad

| Algoritmo | Complejidad temporal | Comparaciones |
|---|---|---|
| Fuerza bruta | `O(n²)` | `n(n−1)/2` |
| Dividir y conquistar | `O(n log n)` | `O(n log n)` |

Incluso en un arreglo ya ordenado, dividir y conquistar realiza comparaciones durante las mezclas. En cambio, Merge Sort con una comprobación previa del orden podría hacer solo `n−1` comparaciones, pero esa optimización no forma parte de este taller.

**Importante:** para arreglos grandes, el número de inversiones puede superar el límite de un entero de 32 bits. Utiliza enteros de 64 bits (`long long` en C/C++ o `long` en Java).

## 4. Formato de entrada (VPL)

La entrada tiene el siguiente formato:

```text
T
n1
a1 a2 ... an1
n2
a1 a2 ... an2
...
```

Donde:

- `T`: número de casos de prueba.
- `n`: tamaño del arreglo.
- `a1, a2, ..., an`: elementos del arreglo, separados por espacios.

Los valores pueden repetirse.

## 5. Formato de salida esperada

Por cada caso de prueba, se debe imprimir una línea con tres enteros separados por espacios:

```text
inversiones comparaciones_fuerza_bruta comparaciones_dyc
```

No se deben imprimir mensajes adicionales, títulos ni explicaciones en la salida del programa.

## 6. Ejemplo

### Entrada

```text
2
5
2 4 1 3 5
4
1 2 3 4
```

### Salida esperada

```text
3 10 7
0 6 4
```

### Verificación del primer caso

Para el arreglo `2 4 1 3 5`, las inversiones son:

- `(2, 1)`
- `(4, 1)`
- `(4, 3)`

Por tanto, hay `3` inversiones.

La fuerza bruta revisa los `5 × 4 / 2 = 10` pares posibles, mientras que dividir y conquistar realiza `7` comparaciones durante las mezclas.

En el segundo caso, el arreglo `1 2 3 4` está ordenado y tiene `0` inversiones. La fuerza bruta realiza `6` comparaciones y dividir y conquistar realiza `4`.

## 7. Objetivo del análisis experimental

Con los resultados obtenidos, compara ambos algoritmos para diferentes tipos de arreglos:

- Arreglos ordenados de menor a mayor.
- Arreglos ordenados de mayor a menor.
- Arreglos aleatorios.
- Arreglos con elementos repetidos.

Analiza cómo cambia el número de inversiones y de comparaciones en cada caso, y determina si dividir y conquistar siempre realiza menos comparaciones que la fuerza bruta.
