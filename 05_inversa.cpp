/**
 * ============================================================================
 * ARCHIVO: 05_inversa.cpp
 * PROPÓSITO: Cálculo de la matriz inversa
 * CONCEPTOS: Matriz inversa, adjunta, cofactores, sistemas lineales
 * 
 * TEORÍA COMPLETA DE LA MATRIZ INVERSA:
 * 
 * DEFINICIÓN:
 * A⁻¹ es la matriz tal que A·A⁻¹ = A⁻¹·A = I
 * Solo existe si det(A) ≠ 0 (matriz no singular)
 * 
 * MÉTODOS DE CÁLCULO:
 * 
 * 1. MÉTODO DE LA ADJUNTA (usado aquí):
 *    A⁻¹ = (1/det(A)) · adj(A)
 *    donde adj(A) = (cof(A))^T
 *    
 *    cof(A)ᵢⱼ = (-1)^(i+j) · det(Mᵢⱼ)
 * 
 * 2. MÉTODO DE GAUSS-JORDAN:
 *    [A | I] → [I | A⁻¹] mediante operaciones elementales
 * 
 * 3. DESCOMPOSICIÓN LU:
 *    A = LU → A⁻¹ = U⁻¹L⁻¹
 * 
 * PROPIEDADES IMPORTANTES:
 * 1. (A⁻¹)⁻¹ = A
 * 2. (AB)⁻¹ = B⁻¹A⁻¹
 * 3. (A^T)⁻¹ = (A⁻¹)^T
 * 4. det(A⁻¹) = 1/det(A)
 * 
 * APLICACIONES:
 * - Resolución de sistemas: x = A⁻¹b
 * - Codificación/decodificación
 * - Transformaciones inversas en gráficos
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "04_determinante_gauss.cpp"

/**
 * NOMBRE: calcularMatrizCofactores
 * PROPÓSITO: Calcula la matriz de cofactores de una matriz cuadrada
 * 
 * EXPLICACIÓN:
 * El cofactor Cᵢⱼ = (-1)^(i+j) · det(Mᵢⱼ)
 * donde Mᵢⱼ es el menor complementario (matriz sin fila i ni columna j)
 * 
 * @param matriz Matriz original
 * @param cofactores Matriz de cofactores resultante
 * @param n Dimensión
 */
void calcularMatrizCofactores(double matriz[][MAX_COLUMNAS], double cofactores[][MAX_COLUMNAS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Obtener el menor complementario Mᵢⱼ
            double submatriz[MAX_FILAS][MAX_COLUMNAS];
            obtenerSubmatriz(matriz, submatriz, n, i, j);
            
            // Calcular su determinante (usamos Gauss por eficiencia)
            double det = calcularDeterminanteGauss(submatriz, n - 1);
            
            // Aplicar signo: (-1)^(i+j)
            if ((i + j) % 2 == 0) {
                cofactores[i][j] = det;
            } else {
                cofactores[i][j] = -det;
            }
        }
    }
}

/**
 * NOMBRE: calcularAdjunta
 * PROPÓSITO: Calcula la matriz adjunta (transpuesta de la matriz de cofactores)
 * 
 * EXPLICACIÓN:
 * adj(A) = (cof(A))^T
 * La adjunta es crucial porque A⁻¹ = (1/det(A)) · adj(A)
 * 
 * @param matriz Matriz original
 * @param adjunta Matriz adjunta resultante
 * @param n Dimensión
 */
void calcularAdjunta(double matriz[][MAX_COLUMNAS], double adjunta[][MAX_COLUMNAS], int n) {
    double cofactores[MAX_FILAS][MAX_COLUMNAS];
    calcularMatrizCofactores(matriz, cofactores, n);
    
    // Transponer la matriz de cofactores
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjunta[j][i] = cofactores[i][j];
        }
    }
}

/**
 * NOMBRE: calcularInversa
 * PROPÓSITO: Calcula la matriz inversa usando el método de la adjunta
 * 
 * EXPLICACIÓN DETALLADA DEL ALGORITMO:
 * 
 * PASOS:
 * 1. Verificar que la matriz sea cuadrada
 * 2. Calcular el determinante (si es 0, no hay inversa)
 * 3. Calcular la matriz de cofactores
 * 4. Transponer para obtener la adjunta
 * 5. Dividir cada elemento por el determinante
 * 
 * @param matriz Matriz original
 * @param inversa Matriz inversa resultante
 * @param n Dimensión
 * @return true si la matriz es invertible
 */
bool calcularInversa(double matriz[][MAX_COLUMNAS], double inversa[][MAX_COLUMNAS], int n) {
    // Verificar que la matriz sea cuadrada
    if (n <= 0) return false;
    
    // Calcular determinante
    double det = calcularDeterminanteGauss(matriz, n);
    
    // Verificar invertibilidad
    if (std::fabs(det) < TOLERANCIA) {
        return false;  // Matriz singular (no invertible)
    }
    
    // Calcular matriz adjunta
    double adjunta[MAX_FILAS][MAX_COLUMNAS];
    calcularAdjunta(matriz, adjunta, n);
    
    // Calcular inversa: A⁻¹ = (1/det) · adj(A)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversa[i][j] = adjunta[i][j] / det;
        }
    }
    
    return true;
}

/**
 * NOMBRE: verificarInversa
 * PROPÓSITO: Verifica que A * A⁻¹ = I
 * 
 * EXPLICACIÓN:
 * Esta función comprueba la corrección del cálculo multiplicando
 * la matriz original por su supuesta inversa y verificando que
 * el resultado sea la identidad.
 * 
 * @param matriz Matriz original
 * @param inversa Matriz inversa calculada
 * @param n Dimensión
 * @return true si la verificación es exitosa
 */
bool verificarInversa(double matriz[][MAX_COLUMNAS], double inversa[][MAX_COLUMNAS], int n) {
    double producto[MAX_FILAS][MAX_COLUMNAS];
    multiplicarMatrices(matriz, inversa, producto, n, n, n);
    
    // Crear matriz identidad esperada
    double identidad[MAX_FILAS][MAX_COLUMNAS];
    inicializarIdentidad(identidad, n);
    
    // Comparar
    return sonMatricesIguales(producto, identidad, n, n);
}