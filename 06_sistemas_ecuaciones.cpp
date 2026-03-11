/**
 * ============================================================================
 * ARCHIVO: 06_sistemas_ecuaciones.cpp
 * PROPÓSITO: Resolución de sistemas de ecuaciones lineales
 * CONCEPTOS: Sistemas lineales, regla de Cramer, eliminación gaussiana
 * 
 * TEORÍA DE SISTEMAS LINEALES:
 * 
 * FORMA MATRICIAL:
 * Ax = b, donde:
 * - A: matriz de coeficientes (m×n)
 * - x: vector de incógnitas (n×1)
 * - b: vector de términos independientes (m×1)
 * 
 * CLASIFICACIÓN DE SISTEMAS:
 * 
 * 1. Sistema Compatible Determinado (SCD):
 *    - Una única solución
 *    - det(A) ≠ 0, A es cuadrada
 * 
 * 2. Sistema Compatible Indeterminado (SCI):
 *    - Infinitas soluciones
 *    - det(A) = 0, rango(A) = rango(A|b) < n
 * 
 * 3. Sistema Incompatible (SI):
 *    - Sin solución
 *    - rango(A) < rango(A|b)
 * 
 * MÉTODOS DE RESOLUCIÓN:
 * 
 * 1. REGLA DE CRAMER (para sistemas cuadrados):
 *    xᵢ = det(Aᵢ) / det(A)
 *    donde Aᵢ es A con columna i reemplazada por b
 * 
 * 2. ELIMINACIÓN GAUSSIANA:
 *    Transformar [A|b] a forma triangular y resolver
 * 
 * 3. MATRIZ INVERSA:
 *    x = A⁻¹b (si det(A) ≠ 0)
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "05_inversa.cpp"

/**
 * NOMBRE: resolverSistemaCramer
 * PROPÓSITO: Resuelve un sistema usando la regla de Cramer
 * 
 * EXPLICACIÓN DE LA REGLA DE CRAMER:
 * 
 * Para un sistema Ax = b con A cuadrada (n×n) y det(A) ≠ 0:
 * 
 * x₁ = det(A₁)/det(A)
 * x₂ = det(A₂)/det(A)
 * ...
 * xₙ = det(Aₙ)/det(A)
 * 
 * donde Aⱼ es la matriz obtenida al reemplazar la columna j
 * de A por el vector b.
 * 
 * COMPLEJIDAD: O(n! · n) - solo para sistemas pequeños
 * 
 * @param A Matriz de coeficientes
 * @param b Vector de términos independientes (como matriz columna)
 * @param x Vector solución
 * @param n Dimensión del sistema
 * @return true si el sistema tiene solución única
 */
bool resolverSistemaCramer(double A[][MAX_COLUMNAS], double b[][MAX_COLUMNAS], 
                          double x[][MAX_COLUMNAS], int n) {
    // Calcular determinante de A
    double detA = calcularDeterminanteGauss(A, n);
    
    if (std::fabs(detA) < TOLERANCIA) {
        return false;  // Sistema sin solución única
    }
    
    // Para cada incógnita
    for (int j = 0; j < n; j++) {
        // Crear matriz Aⱼ reemplazando columna j por b
        double Aj[MAX_FILAS][MAX_COLUMNAS];
        copiarMatriz(A, Aj, n, n);
        
        for (int i = 0; i < n; i++) {
            Aj[i][j] = b[i][0];  // Reemplazar columna j
        }
        
        // Calcular det(Aⱼ)
        double detAj = calcularDeterminanteGauss(Aj, n);
        
        // Aplicar regla de Cramer: xⱼ = det(Aⱼ)/det(A)
        x[j][0] = detAj / detA;
    }
    
    return true;
}

/**
 * NOMBRE: resolverSistemaGauss
 * PROPÓSITO: Resuelve un sistema usando eliminación gaussiana
 * 
 * EXPLICACIÓN DEL ALGORITMO:
 * 
 * FASE 1: ELIMINACIÓN PROGRESIVA
 * Convertir [A|b] en forma triangular superior:
 * Para i = 1 to n-1:
 *   Para k = i+1 to n:
 *     factor = A[k][i] / A[i][i]
 *     Para j = i to n:
 *       A[k][j] -= factor * A[i][j]
 *     b[k] -= factor * b[i]
 * 
 * FASE 2: SUSTITUCIÓN REGRESIVA
 * Resolver el sistema triangular:
 * xₙ = bₙ / A[n][n]
 * Para i = n-1 down to 1:
 *   xᵢ = (bᵢ - Σⱼ₌ᵢ₊₁ⁿ A[i][j]·xⱼ) / A[i][i]
 * 
 * @param A Matriz de coeficientes
 * @param b Vector de términos independientes
 * @param x Vector solución
 * @param n Dimensión
 * @return true si el sistema tiene solución
 */
bool resolverSistemaGauss(double A[][MAX_COLUMNAS], double b[][MAX_COLUMNAS], 
                         double x[][MAX_COLUMNAS], int n) {
    // Crear copias para no modificar originales
    double Acopy[MAX_FILAS][MAX_COLUMNAS];
    double bcopy[MAX_FILAS][MAX_COLUMNAS];
    copiarMatriz(A, Acopy, n, n);
    copiarMatriz(b, bcopy, n, 1);
    
    // FASE 1: Eliminación progresiva
    for (int i = 0; i < n - 1; i++) {
        // Buscar pivote
        int maxFila = i;
        for (int k = i + 1; k < n; k++) {
            if (std::fabs(Acopy[k][i]) > std::fabs(Acopy[maxFila][i])) {
                maxFila = k;
            }
        }
        
        if (std::fabs(Acopy[maxFila][i]) < TOLERANCIA) {
            return false;  // Sistema singular
        }
        
        // Intercambiar filas si necesario
        if (maxFila != i) {
            for (int j = 0; j < n; j++) {
                double temp = Acopy[i][j];
                Acopy[i][j] = Acopy[maxFila][j];
                Acopy[maxFila][j] = temp;
            }
            double temp = bcopy[i][0];
            bcopy[i][0] = bcopy[maxFila][0];
            bcopy[maxFila][0] = temp;
        }
        
        // Eliminar elementos debajo del pivote
        for (int k = i + 1; k < n; k++) {
            double factor = Acopy[k][i] / Acopy[i][i];
            for (int j = i; j < n; j++) {
                Acopy[k][j] -= factor * Acopy[i][j];
            }
            bcopy[k][0] -= factor * bcopy[i][0];
        }
    }
    
    // FASE 2: Sustitución regresiva
    for (int i = n - 1; i >= 0; i--) {
        x[i][0] = bcopy[i][0];
        for (int j = i + 1; j < n; j++) {
            x[i][0] -= Acopy[i][j] * x[j][0];
        }
        if (std::fabs(Acopy[i][i]) < TOLERANCIA) {
            return false;
        }
        x[i][0] /= Acopy[i][i];
    }
    
    return true;
}

/**
 * NOMBRE: resolverSistemaInversa
 * PROPÓSITO: Resuelve un sistema usando matriz inversa
 * 
 * EXPLICACIÓN:
 * Si A es invertible, la solución es x = A⁻¹b
 * Este método es útil cuando se resuelven múltiples sistemas
 * con la misma matriz A pero diferentes b.
 * 
 * @param A Matriz de coeficientes
 * @param b Vector de términos independientes
 * @param x Vector solución
 * @param n Dimensión
 * @return true si el sistema tiene solución
 */
bool resolverSistemaInversa(double A[][MAX_COLUMNAS], double b[][MAX_COLUMNAS], 
                           double x[][MAX_COLUMNAS], int n) {
    double inversaA[MAX_FILAS][MAX_COLUMNAS];
    
    if (!calcularInversa(A, inversaA, n)) {
        return false;
    }
    
    // x = A⁻¹ * b
    return multiplicarMatrices(inversaA, b, x, n, n, 1);
}

/**
 * NOMBRE: clasificarSistema
 * PROPÓSITO: Determina el tipo de sistema lineal
 * 
 * EXPLICACIÓN:
 * Analiza la matriz de coeficientes y la matriz ampliada
 * para clasificar el sistema.
 * 
 * @param A Matriz de coeficientes
 * @param b Vector de términos independientes
 * @param n Dimensión
 * @param m Número de ecuaciones
 */
void clasificarSistema(double A[][MAX_COLUMNAS], double b[][MAX_COLUMNAS], int n, int m) {
    std::cout << "\n=== CLASIFICACIÓN DEL SISTEMA ===" << std::endl;
    
    if (n != m) {
        std::cout << "Sistema no cuadrado (" << m << " ecuaciones, " 
                  << n << " incógnitas)" << std::endl;
        return;
    }
    
    double detA = calcularDeterminanteGauss(A, n);
    
    if (std::fabs(detA) > TOLERANCIA) {
        std::cout << "SISTEMA COMPATIBLE DETERMINADO (SCD)" << std::endl;
        std::cout << "- Una única solución" << std::endl;
        std::cout << "- det(A) = " << detA << " ≠ 0" << std::endl;
    } else {
        std::cout << "SISTEMA COMPATIBLE INDETERMINADO O INCOMPATIBLE" << std::endl;
        std::cout << "- det(A) = 0" << std::endl;
        std::cout << "- Se requiere análisis de rangos para más detalles" << std::endl;
    }
}