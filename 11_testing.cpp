/**
 * ============================================================================
 * ARCHIVO: 11_testing.cpp
 * PROPÓSITO: Pruebas exhaustivas de todas las funcionalidades
 * CONCEPTOS: Verificación, validación, casos límite
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include "10_aplicaciones.cpp"

/**
 * NOMBRE: testOperacionesBasicas
 * PROPÓSITO: Prueba suma, resta y multiplicación
 */
void testOperacionesBasicas() {
    std::cout << "\n--- TEST: OPERACIONES BÁSICAS ---" << std::endl;
    
    double A[MAX_FILAS][MAX_COLUMNAS] = {{1, 2}, {3, 4}};
    double B[MAX_FILAS][MAX_COLUMNAS] = {{5, 6}, {7, 8}};
    double esperadoSuma[MAX_FILAS][MAX_COLUMNAS] = {{6, 8}, {10, 12}};
    double esperadoMult[MAX_FILAS][MAX_COLUMNAS] = {{19, 22}, {43, 50}};
    double resultado[MAX_FILAS][MAX_COLUMNAS];
    
    sumarMatrices(A, B, resultado, 2, 2);
    std::cout << "Suma: " << (sonMatricesIguales(resultado, esperadoSuma, 2, 2) ? "✓" : "✗") << std::endl;
    
    multiplicarMatrices(A, B, resultado, 2, 2, 2);
    std::cout << "Multiplicación: " << (sonMatricesIguales(resultado, esperadoMult, 2, 2) ? "✓" : "✗") << std::endl;
}

/**
 * NOMBRE: testDeterminantes
 * PROPÓSITO: Prueba cálculo de determinantes con varios casos
 */
void testDeterminantes() {
    std::cout << "\n--- TEST: DETERMINANTES ---" << std::endl;
    
    // Caso 1: Matriz 2x2
    double A2[MAX_FILAS][MAX_COLUMNAS] = {{4, 6}, {3, 8}};
    double det2 = calcularDeterminanteGauss(A2, 2);
    std::cout << "det 2x2 (14): " << det2 << " - " << (std::fabs(det2 - 14) < TOLERANCIA ? "✓" : "✗") << std::endl;
    
    // Caso 2: Matriz 3x3
    double A3[MAX_FILAS][MAX_COLUMNAS] = {
        {6, 1, 1},
        {4, -2, 5},
        {2, 8, 7}
    };
    double det3 = calcularDeterminanteGauss(A3, 3);
    std::cout << "det 3x3 (-306): " << det3 << " - " << (std::fabs(det3 + 306) < TOLERANCIA ? "✓" : "✗") << std::endl;
    
    // Caso 3: Matriz singular
    double singular[MAX_FILAS][MAX_COLUMNAS] = {{1, 2}, {2, 4}};
    double detSing = calcularDeterminanteGauss(singular, 2);
    std::cout << "det singular (0): " << detSing << " - " << (std::fabs(detSing) < TOLERANCIA ? "✓" : "✗") << std::endl;
}

/**
 * NOMBRE: testInversa
 * PROPÓSITO: Prueba cálculo de matriz inversa
 */
void testInversa() {
    std::cout << "\n--- TEST: MATRIZ INVERSA ---" << std::endl;
    
    double A[MAX_FILAS][MAX_COLUMNAS] = {{4, 7}, {2, 6}};
    double inversa[MAX_FILAS][MAX_COLUMNAS];
    
    if (calcularInversa(A, inversa, 2)) {
        std::cout << "Inversa calculada" << std::endl;
        std::cout << "Verificación A·A⁻¹ = I: " 
                  << (verificarInversa(A, inversa, 2) ? "✓" : "✗") << std::endl;
    } else {
        std::cout << "✗ No se pudo calcular la inversa" << std::endl;
    }
}

/**
 * NOMBRE: testSistemas
 * PROPÓSITO: Prueba resolución de sistemas de ecuaciones
 */
void testSistemas() {
    std::cout << "\n--- TEST: SISTEMAS DE ECUACIONES ---" << std::endl;
    
    // Sistema: 2x + y = 5, x - y = 1
    double A[MAX_FILAS][MAX_COLUMNAS] = {{2, 1}, {1, -1}};
    double b[MAX_FILAS][MAX_COLUMNAS] = {{5}, {1}};
    double x[MAX_FILAS][MAX_COLUMNAS];
    double esperadoX[MAX_FILAS][MAX_COLUMNAS] = {{2}, {1}};  // Solución: x=2, y=1
    
    if (resolverSistemaGauss(A, b, x, 2)) {
        std::cout << "Solución por Gauss: [" << x[0][0] << ", " << x[1][0] << "]" << std::endl;
        std::cout << "Comparación: " << (sonMatricesIguales(x, esperadoX, 2, 1) ? "✓" : "✗") << std::endl;
    }
    
    if (resolverSistemaCramer(A, b, x, 2)) {
        std::cout << "Solución por Cramer: [" << x[0][0] << ", " << x[1][0] << "]" << std::endl;
        std::cout << "Comparación: " << (sonMatricesIguales(x, esperadoX, 2, 1) ? "✓" : "✗") << std::endl;
    }
}

/**
 * NOMBRE: testAplicaciones
 * PROPÓSITO: Prueba aplicaciones prácticas
 */
void testAplicaciones() {
    std::cout << "\n--- TEST: APLICACIONES PRÁCTICAS ---" << std::endl;
    
    // Regresión lineal
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {2, 4, 5, 8, 9};
    double beta0, beta1;
    
    regresionLineal(x, y, 5, beta0, beta1);
    std::cout << "Regresión lineal: y = " << beta0 << " + " << beta1 << "x" << std::endl;
    
    // Rotación 2D
    double xr, yr;
    transformacionRotacion2D(1, 0, 3.14159/2, xr, yr);  // Rotar 90°
    std::cout << "Rotación (1,0) 90° → (" << xr << ", " << yr << ")" << std::endl;
}

/**
 * NOMBRE: ejecutarTodasLasPruebas
 * PROPÓSITO: Ejecuta todas las pruebas unitarias
 */
void ejecutarTodasLasPruebas() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "          EJECUTANDO PRUEBAS EXHAUSTIVAS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    testOperacionesBasicas();
    testDeterminantes();
    testInversa();
    testSistemas();
    testAplicaciones();
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "              PRUEBAS COMPLETADAS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}