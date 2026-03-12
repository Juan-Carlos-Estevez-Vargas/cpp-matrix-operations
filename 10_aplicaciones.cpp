/**
 * ============================================================================
 * ARCHIVO: 10_aplicaciones.cpp
 * PROPÓSITO: Aplicaciones prácticas de matrices
 * CONCEPTOS: Regresión lineal, transformaciones, cadenas de Markov
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "09_operaciones_avanzadas.cpp"

/**
 * NOMBRE: regresionLineal
 * PROPÓSITO: Calcula regresión lineal usando mínimos cuadrados
 * 
 * EXPLICACIÓN:
 * Dados puntos (xᵢ, yᵢ), buscamos y = β₀ + β₁x que minimice
 * Σ (yᵢ - (β₀ + β₁xᵢ))²
 * 
 * Solución matricial: (X^T X) β = X^T y
 * donde X es la matriz de diseño con una columna de 1's
 * 
 * @param x Vector de coordenadas x
 * @param y Vector de coordenadas y
 * @param n Número de puntos
 * @param beta0 Término independiente
 * @param beta1 Pendiente
 */
void regresionLineal(double x[], double y[], int n, double &beta0, double &beta1) {
    // Construir matriz de diseño X
    double X[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < n; i++) {
        X[i][0] = 1.0;  // Columna de unos para β₀
        X[i][1] = x[i]; // Columna de x para β₁
    }
    
    // Vector y como matriz columna
    double Y[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < n; i++) {
        Y[i][0] = y[i];
    }
    
    // Calcular X^T
    double XT[MAX_FILAS][MAX_COLUMNAS];
    calcularTranspuesta(X, XT, n, 2);
    
    // Calcular X^T X
    double XTX[MAX_FILAS][MAX_COLUMNAS];
    multiplicarMatrices(XT, X, XTX, 2, n, 2);
    
    // Calcular X^T y
    double XTy[MAX_FILAS][MAX_COLUMNAS];
    multiplicarMatrices(XT, Y, XTy, 2, n, 1);
    
    // Resolver sistema (X^T X) β = X^T y
    double beta[MAX_FILAS][MAX_COLUMNAS];
    resolverSistemaGauss(XTX, XTy, beta, 2);
    
    beta0 = beta[0][0];
    beta1 = beta[1][0];
}

/**
 * NOMBRE: transformacionRotacion2D
 * PROPÓSITO: Aplica rotación 2D a un punto
 * 
 * EXPLICACIÓN:
 * Matriz de rotación: R(θ) = [cosθ  -sinθ; sinθ  cosθ]
 * 
 * @param x Coordenada x original
 * @param y Coordenada y original
 * @param angulo Ángulo en radianes
 * @param xr Coordenada x rotada
 * @param yr Coordenada y rotada
 */
void transformacionRotacion2D(double x, double y, double angulo, double &xr, double &yr) {
    double R[MAX_FILAS][MAX_COLUMNAS] = {
        {std::cos(angulo), -std::sin(angulo)},
        {std::sin(angulo), std::cos(angulo)}
    };
    
    double punto[MAX_FILAS][MAX_COLUMNAS] = {{x}, {y}};
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    
    multiplicarMatrices(R, punto, resultado, 2, 2, 1);
    
    xr = resultado[0][0];
    yr = resultado[1][0];
}

/**
 * NOMBRE: cadenaMarkov
 * PROPÓSITO: Simula una cadena de Markov
 * 
 * EXPLICACIÓN:
 * Una cadena de Markov es un proceso estocástico donde
 * el estado futuro depende solo del estado actual.
 * 
 * La matriz de transición P tiene P[i][j] = probabilidad
 * de ir del estado i al estado j.
 * 
 * @param P Matriz de transición
 * @param estadoInicial Vector de probabilidades iniciales
 * @param pasos Número de pasos a simular
 * @param estadoFinal Vector de probabilidades finales
 * @param n Número de estados
 */
void cadenaMarkov(double P[][MAX_COLUMNAS], double estadoInicial[], 
                 int pasos, double estadoFinal[], int n) {
    double estado[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < n; i++) {
        estado[i][0] = estadoInicial[i];
    }
    
    double Pk[MAX_FILAS][MAX_COLUMNAS];
    potenciaMatriz(P, Pk, n, pasos);
    
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    multiplicarMatrices(Pk, estado, resultado, n, n, 1);
    
    for (int i = 0; i < n; i++) {
        estadoFinal[i] = resultado[i][0];
    }
}

/**
 * NOMBRE: calcularTranspuesta
 * PROPÓSITO: Calcula la transpuesta de una matriz
 *
 * EXPLICACIÓN:
 * La transpuesta de una matriz A se obtiene intercambiando
 * filas por columnas:
 *
 * AT[i][j] = A[j][i]
 *
 * @param A Matriz original
 * @param AT Matriz transpuesta
 * @param filas Número de filas de A
 * @param columnas Número de columnas de A
 */
void calcularTranspuesta(double A[][MAX_COLUMNAS], 
                         double AT[][MAX_COLUMNAS], 
                         int filas, int columnas) {

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            AT[j][i] = A[i][j];
        }
    }
}