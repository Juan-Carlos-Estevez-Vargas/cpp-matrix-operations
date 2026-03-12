/**
 * ============================================================================
 * ARCHIVO: 09_operaciones_avanzadas.cpp
 * PROPÓSITO: Operaciones avanzadas con matrices
 * CONCEPTOS: Rango, nulidad, forma canónica, exponencial
 * ============================================================================
 */

#include <iostream>
#include <cmath>
#include "08_descomposiciones.cpp"

/**
 * NOMBRE: calcularRango
 * PROPÓSITO: Calcula el rango de una matriz
 * 
 * EXPLICACIÓN:
 * El rango es el número de filas/columnas linealmente independientes.
 * Es igual al número de pivotes en la eliminación gaussiana.
 * 
 * @param matriz Matriz a analizar
 * @param filas Número de filas
 * @param columnas Número de columnas
 * @return El rango de la matriz
 */
int calcularRango(double matriz[][MAX_COLUMNAS], int filas, int columnas) {
    double temp[MAX_FILAS][MAX_COLUMNAS];
    copiarMatriz(matriz, temp, filas, columnas);
    
    int rango = 0;
    
    for (int i = 0; i < filas; i++) {
        // Encontrar pivote
        int pivoteColumna = -1;
        for (int j = 0; j < columnas; j++) {
            if (std::fabs(temp[i][j]) > TOLERANCIA) {
                pivoteColumna = j;
                break;
            }
        }
        
        if (pivoteColumna >= 0) {
            rango++;
            
            // Eliminar filas debajo
            for (int k = i + 1; k < filas; k++) {
                double factor = temp[k][pivoteColumna] / temp[i][pivoteColumna];
                for (int j = pivoteColumna; j < columnas; j++) {
                    temp[k][j] -= factor * temp[i][j];
                }
            }
        }
    }
    
    return rango;
}

/**
 * NOMBRE: calcularNulidad
 * PROPÓSITO: Calcula la nulidad de una matriz
 * 
 * EXPLICACIÓN:
 * Nulidad = número de columnas - rango
 * Representa la dimensión del espacio nulo (kernel)
 * 
 * @param matriz Matriz a analizar
 * @param filas Número de filas
 * @param columnas Número de columnas
 * @return La nulidad
 */
int calcularNulidad(double matriz[][MAX_COLUMNAS], int filas, int columnas) {
    int rango = calcularRango(matriz, filas, columnas);
    return columnas - rango;
}

/**
 * NOMBRE: exponencialMatriz
 * PROPÓSITO: Calcula la exponencial de una matriz usando serie de Taylor
 * 
 * EXPLICACIÓN:
 * e^A = I + A + A²/2! + A³/3! + ...
 * 
 * @param matriz Matriz original
 * @param resultado Matriz exponencial
 * @param n Dimensión
 * @param terminos Número de términos de la serie
 */
void exponencialMatriz(double matriz[][MAX_COLUMNAS], double resultado[][MAX_COLUMNAS], 
                      int n, int terminos = 10) {
    inicializarIdentidad(resultado, n);
    
    double termino[MAX_FILAS][MAX_COLUMNAS];
    copiarMatriz(matriz, termino, n, n);
    
    double factorial = 1.0;
    
    for (int k = 1; k < terminos; k++) {
        factorial *= k;
        
        // Sumar término: A^k / k!
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                resultado[i][j] += termino[i][j] / factorial;
            }
        }
        
        // Calcular siguiente potencia: A^(k+1)
        double siguiente[MAX_FILAS][MAX_COLUMNAS];
        multiplicarMatrices(termino, matriz, siguiente, n, n, n);
        copiarMatriz(siguiente, termino, n, n);
    }
}