/**
 * ============================================================================
 * ARCHIVO: 01_utils.cpp
 * PROPÓSITO: Funciones utilitarias básicas para manejo de matrices
 * CONCEPTOS: Inicialización, copia, visualización, validación
 * 
 * TEORÍA:
 * Una matriz es una estructura bidimensional que requiere operaciones
 * básicas de manipulación. Estas funciones son los bloques fundamentales
 * para todas las demás operaciones.
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

#ifndef MAX_FILAS
#define MAX_FILAS 15
#define MAX_COLUMNAS 15
#define TOLERANCIA 1e-10
#endif

/**
 * NOMBRE: mostrarMatriz
 * PROPÓSITO: Muestra una matriz en consola con formato profesional
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * La visualización de matrices sigue la notación estándar con corchetes
 * o paréntesis. Usamos el formato | a b c | para facilitar la lectura.
 * 
 * @param matriz Matriz a mostrar
 * @param filas Número de filas
 * @param columnas Número de columnas
 */
void mostrarMatriz(double matriz[][MAX_COLUMNAS], int filas, int columnas) {
    std::cout << "\n";
    for (int i = 0; i < filas; i++) {
        std::cout << "| ";
        for (int j = 0; j < columnas; j++) {
            // Usamos formato de 8 caracteres con 4 decimales para alineación
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) 
                     << matriz[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

/**
 * NOMBRE: inicializarCeros
 * PROPÓSITO: Inicializa todos los elementos de una matriz a cero
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * La matriz cero es el elemento neutro de la suma de matrices.
 * Se denota como 0ₘₓₙ y cumple: A + 0 = A
 * 
 * @param matriz Matriz a inicializar
 * @param filas Número de filas
 * @param columnas Número de columnas
 */
void inicializarCeros(double matriz[][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0.0;
        }
    }
}

/**
 * NOMBRE: inicializarIdentidad
 * PROPÓSITO: Crea una matriz identidad de dimensión n
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * La matriz identidad Iₙ tiene 1's en la diagonal principal y 0's en el resto.
 * Es el elemento neutro de la multiplicación de matrices: A·I = I·A = A
 * También se llama matriz unitaria.
 * 
 * @param matriz Matriz a inicializar
 * @param n Dimensión de la matriz cuadrada
 */
void inicializarIdentidad(double matriz[][MAX_COLUMNAS], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

/**
 * NOMBRE: copiarMatriz
 * PROPÓSITO: Copia el contenido de una matriz a otra
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * Dos matrices son iguales si todos sus elementos correspondientes
 * son iguales. Esta función crea una copia exacta.
 * 
 * @param origen Matriz origen
 * @param destino Matriz destino
 * @param filas Número de filas
 * @param columnas Número de columnas
 */
void copiarMatriz(double origen[][MAX_COLUMNAS], double destino[][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

/**
 * NOMBRE: sonMatricesIguales
 * PROPÓSITO: Compara dos matrices con tolerancia numérica
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * Debido a errores de redondeo en computación, comparamos con una
 * tolerancia ε: |a - b| < ε
 * 
 * @param A Primera matriz
 * @param B Segunda matriz
 * @param filas Número de filas
 * @param columnas Número de columnas
 * @return true si son iguales dentro de la tolerancia
 */
bool sonMatricesIguales(double A[][MAX_COLUMNAS], double B[][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (std::fabs(A[i][j] - B[i][j]) > TOLERANCIA) {
                return false;
            }
        }
    }
    return true;
}

/**
 * NOMBRE: esMatrizCuadrada
 * PROPÓSITO: Verifica si una matriz es cuadrada
 * 
 * EXPLICACIÓN MATEMÁTICA:
 * Una matriz es cuadrada si tiene igual número de filas y columnas.
 * Solo las matrices cuadradas tienen determinante, inversa, traza, etc.
 * 
 * @param filas Número de filas
 * @param columnas Número de columnas
 * @return true si es cuadrada
 */
bool esMatrizCuadrada(int filas, int columnas) {
    return filas == columnas && filas > 0;
}