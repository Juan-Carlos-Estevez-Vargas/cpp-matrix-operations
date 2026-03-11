/**
 * ============================================================================
 * ARCHIVO: 04_determinante_gauss.cpp
 * PROPÓSITO: Cálculo del determinante usando eliminación gaussiana
 * CONCEPTOS: Eliminación gaussiana, pivotes, matrices triangulares
 * 
 * TEORÍA DEL MÉTODO DE GAUSS PARA DETERMINANTES:
 * 
 * FUNDAMENTO:
 * El determinante de una matriz triangular es el producto de los
 * elementos de su diagonal principal. La eliminación gaussiana
 * transforma una matriz en triangular superior mediante operaciones
 * que afectan el determinante de manera controlada.
 * 
 * OPERACIONES ELEMENTALES Y SU EFECTO EN EL DETERMINANTE:
 * 
 * 1. Intercambiar dos filas: el determinante cambia de signo
 *    det(P·A) = -det(A) donde P es matriz de permutación
 * 
 * 2. Multiplicar una fila por un escalar k: det se multiplica por k
 *    No usamos esta operación para no alterar el valor
 * 
 * 3. Sumar un múltiplo de una fila a otra: el determinante NO cambia
 *    Esta es la operación clave para la eliminación
 * 
 * ALGORITMO:
 * 1. Hacer la matriz triangular superior usando eliminación
 * 2. Llevar cuenta de los intercambios de filas
 * 3. El determinante es (-1)^(intercambios) × producto(diagonal)
 * 
 * VENTAJAS:
 * - Complejidad O(n³) vs O(n!) del método de cofactores
 * - Práctico para matrices de hasta cientos de filas
 * - Numéricamente más estable (con pivoteo parcial)
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "03_determinante_cofactores.cpp"

/**
 * NOMBRE: calcularDeterminanteGauss
 * PROPÓSITO: Calcula el determinante usando eliminación gaussiana con pivoteo parcial
 * 
 * EXPLICACIÓN DEL ALGORITMO CON PIVOTEO:
 * 
 * El pivoteo parcial mejora la estabilidad numérica al elegir como
 * pivote el elemento de mayor valor absoluto en la columna actual.
 * 
 * PASOS DETALLADOS:
 * 1. Para cada columna i (de 0 a n-1):
 *    a. Buscar el máximo elemento en |A[i..n-1][i]|
 *    b. Si es casi cero, el determinante es 0
 *    c. Intercambiar filas si es necesario (incrementar contador)
 *    d. Eliminar los elementos debajo del pivote
 * 
 * 2. El determinante es el producto de los pivotes multiplicado
 *    por (-1)^(número de intercambios)
 * 
 * @param matriz Matriz cuadrada
 * @param n Dimensión de la matriz
 * @return El determinante de la matriz
 */
double calcularDeterminanteGauss(double matriz[][MAX_COLUMNAS], int n) {
    // Hacemos una copia para no modificar la original
    double temp[MAX_FILAS][MAX_COLUMNAS];
    copiarMatriz(matriz, temp, n, n);
    
    double determinante = 1.0;
    int intercambios = 0;
    
    for (int i = 0; i < n; i++) {
        // PASO 1: Encontrar el pivote máximo en la columna i
        int maxFila = i;
        double maxValor = std::fabs(temp[i][i]);
        
        for (int k = i + 1; k < n; k++) {
            double valor = std::fabs(temp[k][i]);
            if (valor > maxValor) {
                maxValor = valor;
                maxFila = k;
            }
        }
        
        // PASO 2: Verificar si la matriz es singular
        if (maxValor < TOLERANCIA) {
            return 0.0;  // Determinante es cero
        }
        
        // PASO 3: Intercambiar filas si es necesario
        if (maxFila != i) {
            for (int j = 0; j < n; j++) {
                double swap = temp[i][j];
                temp[i][j] = temp[maxFila][j];
                temp[maxFila][j] = swap;
            }
            intercambios++;  // Cada intercambio multiplica por -1
        }
        
        // PASO 4: Eliminación hacia adelante
        for (int k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }
    
    // PASO 5: El determinante es el producto de la diagonal
    for (int i = 0; i < n; i++) {
        determinante *= temp[i][i];
    }
    
    // PASO 6: Ajustar por intercambios de filas
    if (intercambios % 2 == 1) {
        determinante = -determinante;
    }
    
    return determinante;
}

/**
 * NOMBRE: compararMetodosDeterminante
 * PROPÓSITO: Compara los resultados de ambos métodos
 * 
 * EXPLICACIÓN:
 * Esta función muestra las ventajas y desventajas de cada método
 * y verifica que produzcan resultados similares (dentro de tolerancia)
 * 
 * @param matriz Matriz a analizar
 * @param n Dimensión
 */
void compararMetodosDeterminante(double matriz[][MAX_COLUMNAS], int n) {
    std::cout << "\n=== COMPARACIÓN DE MÉTODOS PARA DETERMINANTE ===" << std::endl;
    
    // Método 1: Cofactores (recursivo)
    clock_t inicio = clock();
    double detCofactores = calcularDeterminanteCofactores(matriz, n);
    clock_t fin = clock();
    double tiempoCofactores = double(fin - inicio) / CLOCKS_PER_SEC;
    
    // Método 2: Gauss (eliminación)
    inicio = clock();
    double detGauss = calcularDeterminanteGauss(matriz, n);
    fin = clock();
    double tiempoGauss = double(fin - inicio) / CLOCKS_PER_SEC;
    
    std::cout << "Método de cofactores: det = " << detCofactores 
              << ", tiempo = " << tiempoCofactores << " segundos" << std::endl;
    std::cout << "Método de Gauss: det = " << detGauss 
              << ", tiempo = " << tiempoGauss << " segundos" << std::endl;
    
    double diferencia = std::fabs(detCofactores - detGauss);
    std::cout << "Diferencia: " << diferencia << std::endl;
    
    if (diferencia < TOLERANCIA) {
        std::cout << "✓ Los métodos coinciden dentro de la tolerancia" << std::endl;
    } else {
        std::cout << "✗ Los métodos NO coinciden (posible inestabilidad numérica)" << std::endl;
    }
    
    std::cout << "\nCONCLUSIÓN EDUCATIVA:" << std::endl;
    std::cout << "- Cofactores: Conceptual, fácil de entender pero lento (O(n!))" << std::endl;
    std::cout << "- Gauss: Práctico, rápido (O(n³)) y estable numéricamente" << std::endl;
}