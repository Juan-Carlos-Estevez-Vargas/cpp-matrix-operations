/**
 * ============================================================================
 * ARCHIVO: 03_determinante_cofactores.cpp
 * PROPÓSITO: Cálculo del determinante usando expansión por cofactores
 * CONCEPTOS: Determinante, menores, cofactores, expansión de Laplace
 * 
 * TEORÍA COMPLETA DEL DETERMINANTE:
 * 
 * DEFINICIÓN:
 * El determinante es una función que asigna un número real a cada matriz cuadrada.
 * Geométricamente, representa el factor de escala del volumen bajo la
 * transformación lineal asociada a la matriz.
 * 
 * PROPIEDADES FUNDAMENTALES:
 * 1. det(I) = 1
 * 2. det(AB) = det(A) · det(B)
 * 3. det(A^T) = det(A)
 * 4. Si A tiene dos filas iguales, det(A) = 0
 * 5. det(A) ≠ 0 ⇔ A es invertible
 * 6. El determinante cambia de signo al intercambiar dos filas
 * 
 * MÉTODO DE COFACTORES (EXPANSIÓN DE LAPLACE):
 * Para una matriz n×n, el determinante se puede calcular expandiendo por
 * cualquier fila o columna:
 * 
 * det(A) = Σⱼ (-1)^(i+j) · aᵢⱼ · det(Mᵢⱼ)
 * 
 * donde Mᵢⱼ es la submatriz obtenida eliminando la fila i y columna j.
 * 
 * COMPLEJIDAD COMPUTACIONAL:
 * Este método tiene complejidad O(n!), por lo que solo es práctico
 * para matrices pequeñas (n ≤ 10). Para matrices grandes se prefiere
 * eliminación gaussiana.
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "02_aritmetica.cpp"

/**
 * NOMBRE: obtenerSubmatriz
 * PROPÓSITO: Obtiene la submatriz eliminando una fila y columna específicas
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * El menor complementario Mᵢⱼ es la matriz que resulta de eliminar
 * la fila i y la columna j de la matriz original. Su determinante
 * se usa en el cálculo de cofactores.
 * 
 * @param matriz Matriz original
 * @param submatriz Submatriz resultante
 * @param n Dimensión de la matriz original
 * @param filaEliminar Fila a eliminar (0-based)
 * @param columnaEliminar Columna a eliminar (0-based)
 */
void obtenerSubmatriz(double matriz[][MAX_COLUMNAS], double submatriz[][MAX_COLUMNAS], 
                     int n, int filaEliminar, int columnaEliminar) {
    int subi = 0;  // Índice para filas de la submatriz
    for (int i = 0; i < n; i++) {
        if (i == filaEliminar) continue;  // Saltar fila eliminada
        
        int subj = 0;  // Índice para columnas de la submatriz
        for (int j = 0; j < n; j++) {
            if (j == columnaEliminar) continue;  // Saltar columna eliminada
            
            submatriz[subi][subj] = matriz[i][j];
            subj++;
        }
        subi++;
    }
}

/**
 * NOMBRE: calcularDeterminanteCofactores
 * PROPÓSITO: Calcula el determinante usando expansión por cofactores (recursivo)
 * 
 * EXPLICACIÓN DETALLADA DEL ALGORITMO:
 * 
 * CASOS BASE:
 * - n = 1: det = único elemento
 * - n = 2: det = ad - bc (fórmula directa)
 * 
 * CASO GENERAL (n > 2):
 * 1. Elegir una fila para expandir (usamos fila 0 por simplicidad)
 * 2. Para cada columna j:
 *    a. Obtener el menor complementario M₀ⱼ
 *    b. Calcular recursivamente det(M₀ⱼ)
 *    c. El cofactor es: C₀ⱼ = (-1)^(0+j) · det(M₀ⱼ)
 *    d. Sumar: det += a₀ⱼ · C₀ⱼ
 * 
 * SIGNO DE LOS COFACTORES:
 * El factor (-1)^(i+j) crea un patrón de tablero de ajedrez:
 *     + - + - ...
 *     - + - + ...
 *     + - + - ...
 * 
 * @param matriz Matriz cuadrada
 * @param n Dimensión de la matriz
 * @return El determinante de la matriz
 */
double calcularDeterminanteCofactores(double matriz[][MAX_COLUMNAS], int n) {
    // Caso base 1: matriz 1x1
    if (n == 1) {
        return matriz[0][0];
    }
    
    // Caso base 2: matriz 2x2 (fórmula directa para eficiencia)
    if (n == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }
    
    double determinante = 0.0;
    
    // Expandimos por la primera fila (i = 0)
    for (int j = 0; j < n; j++) {
        // Obtener el menor complementario M₀ⱼ
        double submatriz[MAX_FILAS][MAX_COLUMNAS];
        obtenerSubmatriz(matriz, submatriz, n, 0, j);
        
        // Calcular recursivamente el determinante del menor
        double detMenor = calcularDeterminanteCofactores(submatriz, n - 1);
        
        // Calcular el cofactor: (-1)^(0+j) * det(M₀ⱼ)
        double cofactor;
        if (j % 2 == 0) {  // (-1)^(0+j) = 1 si j es par
            cofactor = detMenor;
        } else {            // (-1)^(0+j) = -1 si j es impar
            cofactor = -detMenor;
        }
        
        // Sumar término: a₀ⱼ * cofactor
        determinante += matriz[0][j] * cofactor;
    }
    
    return determinante;
}

/**
 * NOMBRE: demostrarPropiedadesDeterminante
 * PROPÓSITO: Demuestra propiedades importantes del determinante
 * 
 * EXPLICACIÓN EDUCATIVA:
 * Esta función muestra ejemplos de las propiedades del determinante
 * para ayudar a comprender el concepto.
 * 
 * @param matriz Matriz de ejemplo
 * @param n Dimensión
 */
void demostrarPropiedadesDeterminante(double matriz[][MAX_COLUMNAS], int n) {
    std::cout << "\n=== DEMOSTRACIÓN DE PROPIEDADES DEL DETERMINANTE ===" << std::endl;
    
    double detOriginal = calcularDeterminanteCofactores(matriz, n);
    std::cout << "Determinante original: " << detOriginal << std::endl;
    
    // Propiedad 1: det(A^T) = det(A)
    double transpuesta[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
    double detTranspuesta = calcularDeterminanteCofactores(transpuesta, n);
    std::cout << "Propiedad 1 - det(A^T) = " << detTranspuesta 
              << " (debe ser igual a " << detOriginal << ")" << std::endl;
    
    // Propiedad 2: Si se multiplica una fila por k, el determinante se multiplica por k
    double matrizEscalada[MAX_FILAS][MAX_COLUMNAS];
    copiarMatriz(matriz, matrizEscalada, n, n);
    double k = 2.5;
    for (int j = 0; j < n; j++) {
        matrizEscalada[0][j] *= k;
    }
    double detEscalada = calcularDeterminanteCofactores(matrizEscalada, n);
    std::cout << "Propiedad 2 - Multiplicar fila 0 por " << k << ": "
              << detEscalada << " = " << k << " * " << detOriginal 
              << " = " << k * detOriginal << std::endl;
}