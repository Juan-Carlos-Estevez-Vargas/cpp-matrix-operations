/**
 * ============================================================================
 * ARCHIVO: 08_descomposiciones.cpp
 * PROPÓSITO: Descomposiciones matriciales: LU, QR
 * CONCEPTOS: Factorización, matrices triangulares, ortogonalidad
 * 
 * TEORÍA DE DESCOMPOSICIONES:
 * 
 * DESCOMPOSICIÓN LU:
 * A = L·U donde:
 * - L: triangular inferior con 1's en diagonal (Lower)
 * - U: triangular superior (Upper)
 * 
 * APLICACIONES:
 * - Resolver múltiples sistemas Ax = b con misma A
 * - Calcular determinante: det(A) = producto(diagonal(U))
 * - Calcular inversa más eficientemente
 * 
 * ALGORITMO DE DOOLITTLE:
 * Para i = 1..n:
 *   Para j = i..n: U[i][j] = A[i][j] - Σ L[i][k]·U[k][j]
 *   Para j = i+1..n: L[j][i] = (A[j][i] - Σ L[j][k]·U[k][i]) / U[i][i]
 * 
 * DESCOMPOSICIÓN QR:
 * A = Q·R donde:
 * - Q: ortogonal (Q^T·Q = I)
 * - R: triangular superior
 * 
 * MÉTODO DE GRAM-SCHMIDT:
 * Ortogonaliza las columnas de A para obtener Q
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "07_valores_propios.cpp"

/**
 * NOMBRE: descomposicionLU
 * PROPÓSITO: Calcula la descomposición LU de una matriz
 * 
 * EXPLICACIÓN DETALLADA:
 * 
 * La descomposición LU existe si todos los menores principales
 * son no singulares (es decir, todos los pivotes no son cero).
 * 
 * @param A Matriz original
 * @param L Matriz triangular inferior
 * @param U Matriz triangular superior
 * @param n Dimensión
 * @return true si la descomposición fue exitosa
 */
bool descomposicionLU(double A[][MAX_COLUMNAS], double L[][MAX_COLUMNAS], 
                     double U[][MAX_COLUMNAS], int n) {
    // Inicializar L como identidad y U como copia de A
    inicializarIdentidad(L, n);
    copiarMatriz(A, U, n, n);
    
    for (int i = 0; i < n; i++) {
        // Verificar pivote
        if (std::fabs(U[i][i]) < TOLERANCIA) {
            return false;  // Se requeriría pivoteo
        }
        
        // Eliminación hacia adelante
        for (int k = i + 1; k < n; k++) {
            double factor = U[k][i] / U[i][i];
            L[k][i] = factor;  // Guardar factor en L
            
            for (int j = i; j < n; j++) {
                U[k][j] -= factor * U[i][j];
            }
        }
    }
    
    return true;
}

/**
 * NOMBRE: resolverLULU
 * PROPÓSITO: Resuelve un sistema usando descomposición LU
 * 
 * EXPLICACIÓN:
 * Si A = LU, entonces Ax = b se resuelve en dos pasos:
 * 1. Ly = b (sustitución progresiva)
 * 2. Ux = y (sustitución regresiva)
 * 
 * @param L Matriz triangular inferior
 * @param U Matriz triangular superior
 * @param b Vector de términos independientes
 * @param x Vector solución
 * @param n Dimensión
 */
void resolverLU(double L[][MAX_COLUMNAS], double U[][MAX_COLUMNAS], 
               double b[][MAX_COLUMNAS], double x[][MAX_COLUMNAS], int n) {
    double y[MAX_FILAS][MAX_COLUMNAS] = {{0}};
    
    // Sustitución progresiva: Ly = b
    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * y[j][0];
        }
        y[i][0] = b[i][0] - suma;
    }
    
    // Sustitución regresiva: Ux = y
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0.0;
        for (int j = i + 1; j < n; j++) {
            suma += U[i][j] * x[j][0];
        }
        x[i][0] = (y[i][0] - suma) / U[i][i];
    }
}

/**
 * NOMBRE: descomposicionQRGramSchmidt
 * PROPÓSITO: Calcula la descomposición QR usando Gram-Schmidt
 * 
 * EXPLICACIÓN DEL MÉTODO DE GRAM-SCHMIDT:
 * 
 * Dada A = [a₁ a₂ ... aₙ], queremos Q = [q₁ q₂ ... qₙ] ortogonal.
 * 
 * PASOS:
 * 1. q₁ = a₁ / ||a₁||
 * 2. Para k = 2..n:
 *    Proyectar aₖ sobre los q anteriores y restar
 *    qₖ = aₖ - Σ (qⱼ^T·aₖ) qⱼ
 *    Normalizar qₖ
 * 
 * 3. Rⱼₖ = qⱼ^T·aₖ para j ≤ k
 * 
 * @param A Matriz original
 * @param Q Matriz ortogonal
 * @param R Matriz triangular superior
 * @param m Filas de A
 * @param n Columnas de A
 */
void descomposicionQRGramSchmidt(double A[][MAX_COLUMNAS], double Q[][MAX_COLUMNAS], 
                                double R[][MAX_COLUMNAS], int m, int n) {
    // Inicializar R con ceros
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = 0.0;
        }
    }
    
    for (int k = 0; k < n; k++) {
        // Tomar columna k de A
        double v[MAX_FILAS];
        for (int i = 0; i < m; i++) {
            v[i] = A[i][k];
        }
        
        // Proyectar sobre vectores previos
        for (int j = 0; j < k; j++) {
            // Calcular proyección: qⱼ^T·aₖ
            double proyeccion = 0.0;
            for (int i = 0; i < m; i++) {
                proyeccion += Q[i][j] * A[i][k];
            }
            R[j][k] = proyeccion;
            
            // Restar proyección
            for (int i = 0; i < m; i++) {
                v[i] -= proyeccion * Q[i][j];
            }
        }
        
        // Normalizar para obtener qₖ
        double norma = 0.0;
        for (int i = 0; i < m; i++) {
            norma += v[i] * v[i];
        }
        norma = std::sqrt(norma);
        
        if (norma > TOLERANCIA) {
            for (int i = 0; i < m; i++) {
                Q[i][k] = v[i] / norma;
            }
            R[k][k] = norma;
        }
    }
}